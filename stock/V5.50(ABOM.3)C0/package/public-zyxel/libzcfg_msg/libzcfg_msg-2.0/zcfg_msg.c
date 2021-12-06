/*!
 *  @file zcfg_msg.c
 *      The library is for IPC communications per thread. Process is kind of thread.
 *
 *  @author     CP Wang
 *  @date       2017-09-28 11:47:03
 *  @copyright  Copyright ?2017 Zyxel Communications Corp. All Rights Reserved.
 *
 *  @note       The initialization sequence is very important because if it is wrong
 *              then the functions will not work normally.
 *              And, the sequence is as follows.
 *              1. Main process calls zcfgEidInit().
 *              2. After step 1 is done successfully, main process creates threads.
 */
//==============================================================================
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/un.h>

#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <syslog.h>

#include "zcfg_msg.h"
#include "zlog_api.h"
#include "zos_api.h"

//==============================================================================
#define _MAX_THREADS            16
#define _SEND_TRY_MAX_CNT       3

#define _MUTEX_LOCK()           pthread_mutex_lock(&_mutex)
#define _MUTEX_UNLOCK()         pthread_mutex_unlock(&_mutex)

//==============================================================================
/*
    1. if eid <= 0 then the entry is not in use.
    2. pid is the index
*/
typedef struct
{
    zcfg_msg_eid_t      eid;
    uint32_t            pid;
    int                 sck_id;
} _msg_data_s;

//==============================================================================
static bool             _init  = false;
static pthread_mutex_t  _mutex = PTHREAD_MUTEX_INITIALIZER;
static _msg_data_s      _msg_data[_MAX_THREADS];

static uint32_t         _zcfg_msg_req_idx = 0;

//==============================================================================
/*!
 *  find an entry that is free, i.e., not in use.
 *
 *  @return _msg_data_s*    pointer of free entry
 *          NULL            no entry is free
 */
static _msg_data_s *_free_msg_data_get()
{
    int     i;

    for (i = 0; i < _MAX_THREADS; ++i)
    {
        if (_msg_data[i].eid <= 0)
        {
            return(&_msg_data[i]);
        }
    }
    return NULL;
}

/*!
 *  find my entry.
 *  if not found data for my own thread, then use the process one.
 *
 *  @return _msg_data_s*    pointer of my entry
 *          NULL            no entry is free
 */
static _msg_data_s *_my_msg_data_get()
{
    int         i;
    uint32_t    my_pid;

    if (_init == false)
    {
        ZLOG_ERROR("not initialized yet");
        return NULL;
    }

    my_pid = zos_pid_get();

    for (i = 0; i < _MAX_THREADS; ++i)
    {
        if (_msg_data[i].pid == my_pid)
        {
            return(&_msg_data[i]);
        }
    }

    /*
        If not found data for my own thread, then use the process one.
    */
    if (_msg_data[0].eid > 0)
    {
        return(&_msg_data[0]);
    }

    return NULL;
}

/*!
 *  Allocate memory with size, which will be aligned with 1024 to avoid fragmentation.
 *
 *  @param [in] size    memory size to be allocated
 *
 *  @return char*   memory pointer allocated
 *          NULL    fail to allocate memory due to memory insufficient
 */
static char *_msg_alloc
(
    int     size
)
{
    char *ptr;

    if (size <= 0)
    {
        return NULL;
    }

    ptr = (char *)ZOS_MALLOC((size / 1024 + 1) * 1024);

    if (ptr == NULL)
    {
        ZLOG_CRITICAL("memory insufficient");
    }

    return ptr;
}

/*!
 *  receive message thru socket with timeout.
 *
 *  @param [in]  eid            EID of current thread
 *  @param [in]  sck_id         socket ID to receive message
 *  @param [in]  b_server       true if it is server socket
 *  @param [out] recvBuf        if receiving successfully, recvBuf will be allocated to store the received message
 *  @param [in]  timeout_msec   waiting time in milli-second, ZCFG_MSG_WAIT_FOREVER, ZCFG_MSG_WAIT_NONE
 *  @param [in]  wait_eid       EID we are waiting for, it is valid when b_server is FALSE
 *                              always be 0 if b_server is TRUE
 *  @param [in]  wait_type      wait for the process on the type
 *  @param [in]  wait_oid       wait for the process on the OID
 *
 *  @return ZCFG_SUCCESS    successfully receive
 *          ZCFG_TIMEOUT    time out
 *          others          failed
 *
 *  @note   call should free recvBuf after using it.
 */
static zcfgRet_t _msg_recv
(
    uint32_t            eid,
    int                 sck_id,
    bool                b_server,
    zcfgMsg_t           **recvBuf,
    uint32_t            timeout_msec,
    zcfg_msg_eid_t      wait_eid,
    uint32_t            wait_type,
    uint32_t            wait_oid
)
{
    int                 result;
    socklen_t           fromlen;
    int                 rcvSize;
    uint32_t            clientPid;
    struct timeval      tmpTv;
    struct timeval      *tv;
    struct sockaddr_un  client_addr;
    zcfgMsg_t           rcvMsg;
    fd_set              fdR;
    int                 recv_len;

    if (sck_id < 0)
    {
        ZLOG_ERROR("invalid sck_id = %d", sck_id);
        return ZCFG_INTERNAL_ERROR;
    }

    if (recvBuf == NULL)
    {
        ZLOG_ERROR("recvBuf == NULL");
        return ZCFG_INTERNAL_ERROR;
    }

    // need to wait
    if (timeout_msec != ZCFG_MSG_WAIT_NONE)
    {
        do
        {
            FD_ZERO(&fdR);
            FD_SET(sck_id, &fdR);

            if (timeout_msec == ZCFG_MSG_WAIT_FOREVER)
            {
                // sleep 2 seconds to wait forever
                tmpTv.tv_sec  = 2;
                tmpTv.tv_usec = 0;
            }
            else
            {
                tmpTv.tv_sec  = timeout_msec / 1000;
                tmpTv.tv_usec = (timeout_msec % 1000) * 1000;
            }

            // set tv
            tv = &tmpTv;

            // select and wait
            result = select(sck_id + 1, &fdR, NULL, NULL, tv);

            // timeout
            if (result == 0)
            {
                if (timeout_msec == ZCFG_MSG_WAIT_FOREVER)
                {
                    if (! b_server)
                    {
                        ZLOG_WARNING("EID = %u, select() wait forever, EID = %u, type = %u %s reply, oid = %u",
                            eid, wait_eid, ZCFG_MSG_TYPE(wait_type), ZCFG_MSG_WITH_REPLY_S(wait_type), wait_oid);
                    }
                    continue;
                }
                else
                {
                    ZLOG_WARNING("EID = %u, select() wait for %u milli-seconds, EID = %u, type = %u %s reply, oid = %u",
                        eid, timeout_msec, wait_eid, ZCFG_MSG_TYPE(wait_type), ZCFG_MSG_WITH_REPLY_S(wait_type), wait_oid);
                    return ZCFG_TIMEOUT;
                }
            }

            /* check the select result */
            if (result < 0)
            {
                ZLOG_ERROR("fail to select, EID = %u, wait EID = %u, result = %d, errno = %d, %s",
                    eid, wait_eid, result, errno, strerror(errno));
                return ZCFG_INTERNAL_ERROR;
            }

            // check if I am selected or not
            if (! FD_ISSET(sck_id, &fdR))
            {
                ZLOG_ERROR("my socket is not set in read set, EID = %u, wait EID = %u", eid, wait_eid);
                return ZCFG_INTERNAL_ERROR;
            }

            // yes, this is mine
            break;

        } while(1);

    } // if (timeout_msec != ZCFG_MSG_WAIT_NONE)

    /*
        get message header first to get the total length
        MSG_PEEK
            This flag causes the receive operation to return data from the
            beginning of the receive queue without removing that data from the
            queue. Thus, a subsequent receive call will return the same data.
    */
    fromlen = sizeof(client_addr);
    rcvSize = recvfrom(sck_id, (char *)(&rcvMsg), sizeof(zcfgMsg_t), MSG_PEEK | MSG_WAITALL,
                       (struct sockaddr*)&client_addr, &fromlen);

    if (rcvSize != sizeof(zcfgMsg_t))
    {
        ZLOG_ERROR("fail to recvfrom(MSG_PEEK). EID = %u, wait EID = %u, rcvSize = %d, sizeof(zcfgMsg_t) = %d, errno = %d, %s",
            eid, wait_eid, rcvSize, sizeof(zcfgMsg_t), errno, strerror(errno));
        return ZCFG_INTERNAL_ERROR;
    }

    // get client pid
    clientPid = 0;
    if (b_server)
    {
        sscanf(client_addr.sun_path, "%*[^-]-%u", &clientPid);
        ZLOG_DEBUG("recv from client PID = %u", clientPid);
    }

    /* malloc recv buf size according to length field in msg header */
    recv_len = sizeof(zcfgMsg_t) + rcvMsg.length;
    *recvBuf = (zcfgMsg_t *)_msg_alloc(recv_len + 1);
    if (*recvBuf == NULL)
    {
        ZLOG_ERROR("fail to allocate buffer, size = %d", rcvSize);
        return ZCFG_INTERNAL_ERROR;
    }

    /*
        receive whole message by MSG_WAITALL
    */
    fromlen = sizeof(client_addr);
    rcvSize = recvfrom(sck_id, (char *)(*recvBuf), recv_len, MSG_WAITALL,
                       (struct sockaddr*)&client_addr, &fromlen);

    if (rcvSize != recv_len)
    {
        ZLOG_ERROR("fail to recvfrom(). EID = %u, wait EID = %u, rcvSize = %d, expected recv_len = %d, errno = %d, %s",
            eid, wait_eid, rcvSize, recv_len, errno, strerror(errno));
        ZOS_FREE(*recvBuf);
        return ZCFG_INTERNAL_ERROR;
    }

    // set clientPid
    if (b_server)
    {
        (*recvBuf)->clientPid = clientPid;
    }

    return ZCFG_SUCCESS;

} // _msg_recv

/*
 *  sendMsg will be freed no matter it is successful or not
 */

/*!
 *  send message thru socket till successful.
 *
 *  @param [in]  eid        EID of current thread
 *  @param [in]  sck_id     socket ID to send message
 *  @param [in]  b_server   true if it is server socket
 *  @param [in]  sendMsg    message to be sent, the destination is sendMsg->dstEid
 *
 *  @return ZCFG_SUCCESS    successfully receive
 *          others          failed
 */
static zcfgRet_t _msg_send
(
    uint32_t    eid,
    int         sck_id,
    bool        b_server,
    zcfgMsg_t   *sendMsg
)
{
    socklen_t           addr_len;
    struct sockaddr_un  server_addr;
    int                 total_len;
    char                *ptr;
    int                 n;
    uint32_t            try_cnt;

    ZLOG_DEBUG("sendMsg->srcEid = %d, dstEid = %d, type = %u %s reply, oid = %u",
        sendMsg->srcEid, sendMsg->dstEid, ZCFG_MSG_TYPE(sendMsg->type), ZCFG_MSG_WITH_REPLY_S(sendMsg->type), sendMsg->oid);

#if 0 /* for debug */
    if (sendMsg->dstEid == ZCFG_EID_ESMD)
    {
        ZLOG_INFO("sendMsg->srcEid = %d, dstEid = %d, type = %u %s reply, oid = %u",
            sendMsg->srcEid, sendMsg->dstEid, ZCFG_MSG_TYPE(sendMsg->type), ZCFG_MSG_WITH_REPLY_S(sendMsg->type), sendMsg->oid);
    }
#endif

    if (sck_id < 0)
    {
        ZLOG_ERROR("invalid sck_id = %d", sck_id);
        ZOS_FREE(sendMsg);
        return ZCFG_INTERNAL_ERROR;
    }

    sendMsg->srcEid = eid;
    ZLOG_DEBUG("Assign to my EID, sendMsg->srcEid = %d", sendMsg->srcEid);

    server_addr.sun_family = AF_UNIX;
    if (b_server)
    {
        sprintf(server_addr.sun_path, "%s%hhu-%u", ZCFG_ADDRESS_PREFIX, sendMsg->dstEid, sendMsg->clientPid);
    }
    else
    {
        sprintf(server_addr.sun_path, "%s%hhu", ZCFG_ADDRESS_PREFIX, sendMsg->dstEid);
    }
    addr_len = sizeof(server_addr);

    ZLOG_DEBUG("server_addr.sun_path = %s", server_addr.sun_path);

    ptr       = (char *)sendMsg;
    total_len = sizeof(zcfgMsg_t) + sendMsg->length;
    try_cnt   = 0;

    while (1)
    {
        n = sendto(sck_id, ptr, total_len, 0, (struct sockaddr*)&server_addr, addr_len);

        if (n <= 0)
        {
            if ((try_cnt < _SEND_TRY_MAX_CNT) && (errno == EAGAIN || errno == EWOULDBLOCK))
            {
                ZLOG_WARNING("send again, srcEid = %d, dstEid = %d, type = %u %s reply, oid = %u",
                    sendMsg->srcEid, sendMsg->dstEid, ZCFG_MSG_TYPE(sendMsg->type), ZCFG_MSG_WITH_REPLY_S(sendMsg->type), sendMsg->oid);

                sleep(1); // wait 1 seconds

                if (ZCFG_MSG_WITH_REPLY(sendMsg->type) == false)
                {
                    ++try_cnt;
                }
                continue;
            }

            ZLOG_ERROR("fail to sendto %s, errno = %d(%s), srcEid = %d, dstEid = %d, type = %u %s reply, oid = %u",
                server_addr.sun_path, errno, strerror(errno), sendMsg->srcEid, sendMsg->dstEid, ZCFG_MSG_TYPE(sendMsg->type),
                ZCFG_MSG_WITH_REPLY_S(sendMsg->type), sendMsg->oid);

            ZOS_FREE(sendMsg);
            return ZCFG_INTERNAL_ERROR;
        }

        if (n > total_len)
        {
            ZLOG_ERROR("send more than expected, n(%d) > total_len(%d)", n, total_len);

            ZOS_FREE(sendMsg);
            return ZCFG_INTERNAL_ERROR;
        }

        /*
            update length and buffer pointer
        */
        total_len -= n;
        ptr += n;

        /*
            all sent out
        */
        if (total_len == 0)
        {
            break;
        }

    } // while (1)

    // free message buffer
    ZOS_FREE(sendMsg);

    ZLOG_DEBUG("send successfully");

    // successful
    return ZCFG_SUCCESS;
}

void _init_msg_data()
{
    int     i;

    // already init-ed
    if (_init)
    {
        return;
    }

    // initialize database
    memset(_msg_data, 0, sizeof(_msg_data));

    for (i = 0; i < _MAX_THREADS; ++i)
    {
        _msg_data[i].sck_id = -1;
    }

    _init = true;
}

//==============================================================================
/*!
 *  Initialize EID per thread.
 *
 *  @param [in]  eid            EID
 *  @param [in]  module_name    module name for syslog
 *
 *  @return true    successful
 *          false   fail
 */
bool zcfg_msg_eidInit
(
    zcfg_msg_eid_t      eid,
    char                *module_name
)
{
    _msg_data_s     *free_entry;

    if (ZCFG_MSG_INVALID_EID(eid))
    {
        ZLOG_ERROR("invalid eid = %d", eid);
        return false;
    }

    _MUTEX_LOCK();

    // initialize database
    _init_msg_data();

    // find free entry
    free_entry = _free_msg_data_get();
    if (free_entry == false)
    {
        _MUTEX_UNLOCK();
        ZLOG_ERROR("NO free msg data");
        return false;
    }

    // register into msg data
    free_entry->eid = eid;
    free_entry->pid = zos_pid_get();

    _MUTEX_UNLOCK();

    if (module_name != NULL)
    {
        /* Open a connection to the syslog server */
        openlog(module_name, LOG_NOWAIT | LOG_PID, LOG_USER);
    }

    ZLOG_DEBUG("Register EID %d", eid);

    return true;

} // zcfg_msg_eidInit

/*!
 *  Initialize a server socket per thread to wait for messages from others.
 *
 *  @return ZCFG_SUCCESS    successful
 *          others          fail
 */
zcfgRet_t zcfg_msg_serverInit()
{
    int                     len;
    struct sockaddr_un      saun;
    int                     flags;
    _msg_data_s             *my_entry;

    if (_init == false)
    {
        ZLOG_ERROR("not initialized yet");
        return ZCFG_INTERNAL_ERROR;
    }

    _MUTEX_LOCK();

    my_entry = _my_msg_data_get();

    _MUTEX_UNLOCK();

    if (my_entry == NULL)
    {
        ZLOG_ERROR("fail to get my entry");
        return ZCFG_INTERNAL_ERROR;
    }

    /*
        SOCK_STREAM cannot be used because recvfrom() is called once only.
        if using SOCK_STREAM, then the message may be received in partial,
        but not completely.
    */
    my_entry->sck_id = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (my_entry->sck_id < 0)
    {
        ZLOG_ERROR("create message socket error, my_entry->sck_id = %d, errno = %d, %s",
            my_entry->sck_id, errno, strerror(errno));
        my_entry->sck_id = -1;
        return ZCFG_INTERNAL_ERROR;
    }

    // nonblocking operation
    flags = fcntl(my_entry->sck_id, F_GETFL, 0);
    fcntl(my_entry->sck_id, F_SETFL, flags | O_NONBLOCK);

    // bind server address
    saun.sun_family = AF_UNIX;
    sprintf(saun.sun_path, "%s%u", ZCFG_ADDRESS_PREFIX, my_entry->eid);
    unlink(saun.sun_path);
    len = sizeof(saun);

    if (bind(my_entry->sck_id, (struct sockaddr*)&saun, len) < 0)
    {
        ZLOG_ERROR("bind message socket error. errno = %d, %s", errno, strerror(errno));
        close(my_entry->sck_id);
        my_entry->sck_id = -1;
        return ZCFG_INTERNAL_ERROR;
    }

    ZLOG_INFO("EID %u bind server socket %d on %s successfully", my_entry->eid, my_entry->sck_id, saun.sun_path);

    // allow access
    chmod(saun.sun_path, 0777);

    // successful
    return ZCFG_SUCCESS;

} // zcfg_msg_serverInit

/*!
 *  receive message with timeout.
 *
 *  @param [out] recvBuf        if receiving successfully, recvBuf will be allocated to store the received message
 *  @param [in]  timeout_msec   waiting time in milli-second, ZCFG_MSG_WAIT_FOREVER, ZCFG_MSG_WAIT_NONE
 *
 *  @return ZCFG_SUCCESS    successfully receive
 *          ZCFG_TIMEOUT    time out
 *          others          failed
 *
 *  @note   caller should free recvBuf after using it.
 */
zcfgRet_t zcfg_msg_serverRecv
(
    zcfgMsg_t   **recvBuf,
    uint32_t    timeout_msec
)
{
    _msg_data_s     *my_entry;

    if (_init == false)
    {
        ZLOG_ERROR("not initialized yet");
        return ZCFG_INTERNAL_ERROR;
    }

    _MUTEX_LOCK();

    my_entry = _my_msg_data_get();

    _MUTEX_UNLOCK();

    if (my_entry == NULL)
    {
        ZLOG_ERROR("fail to get my entry");
        return ZCFG_INTERNAL_ERROR;
    }

    return _msg_recv(my_entry->eid, my_entry->sck_id, true, recvBuf, timeout_msec, 0, 0, 0);
}

/*!
 *  send message till successful.
 *
 *  @param [in]  sendMsg    message to be sent, the destination is sendMsg->dstEid
 *
 *  @return ZCFG_SUCCESS    successfully receive
 *          others          failed
 *
 *  @note   sendMsg will be freed anyway
 */
zcfgRet_t zcfg_msg_serverSend
(
    zcfgMsg_t   *sendMsg
)
{
    _msg_data_s     *my_entry;

    if (sendMsg == NULL)
    {
        ZLOG_ERROR("sendMsg == NULL");
        return ZCFG_INTERNAL_ERROR;
    }

    if (_init == false)
    {
        ZLOG_ERROR("not initialized yet");
        ZOS_FREE(sendMsg);
        return ZCFG_INTERNAL_ERROR;
    }

    _MUTEX_LOCK();

    my_entry = _my_msg_data_get();

    _MUTEX_UNLOCK();

    if (my_entry == NULL)
    {
        ZLOG_ERROR("fail to get my entry");
        ZOS_FREE(sendMsg);
        return ZCFG_INTERNAL_ERROR;
    }

    return _msg_send(my_entry->eid, my_entry->sck_id, true, sendMsg);
}

/*!
 *  send message and get reply in timeout.
 *
 *  @param [in]  sendMsg        message to send
 *  @param [out] recvBuf        if receiving successfully, recvBuf will be allocated to store the received message
 *  @param [in]  timeout_msec   waiting time in milli-second, where 0 means wait forever
 *
 *  @return ZCFG_SUCCESS                successfully send and get reply
 *          ZCFG_SUCCESS_AND_NO_REPLY   successfully send without reply
 *          ZCFG_TIMEOUT                time out
 *          others                      failed
 *
 *  @note
 *          - sendMsg will be freed anyway
 *          - caller should free recvBuf after using it if ZCFG_SUCCESS.
 */
zcfgRet_t zcfg_msg_sendAndGetReply
(
    zcfgMsg_t   *sendMsg,
    zcfgMsg_t   **replyMsg,
    uint32_t    timeout_msec
)
{
    int                 fd;
    zcfgRet_t           ret;
    struct sockaddr_un  server_addr;
    int                 flags;
    int                 addrlen;
    uint32_t            seqid;
    zcfg_msg_eid_t      eid;
    zcfg_msg_eid_t      dst_eid;
    uint32_t            send_oid;
    uint32_t            send_type;

    if (sendMsg == NULL)
    {
        ZLOG_ERROR("sendMsg == NULL");
        return ZCFG_INTERNAL_ERROR;
    }

    eid = zcfg_msg_eidGet();

    if (eid == 0)
    {
        ZLOG_ERROR("fail to get my EID");
        ZOS_FREE(sendMsg);
        return ZCFG_INTERNAL_ERROR;
    }

    if (eid != sendMsg->srcEid)
    {
        ZLOG_DEBUG("Invalid sendMsg->srcEid = %d, my EID = %d", sendMsg->srcEid, eid);
    }

#if 0 /* if msg type without reply, then replyMsg can be NULL */
    if (replyMsg == NULL)
    {
        ZLOG_ERROR("replyMsg == NULL");
        ZOS_FREE(sendMsg);
        return ZCFG_INTERNAL_ERROR;
    }
#endif

    // create socket for send
    fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (fd < 0)
    {
        ZLOG_ERROR("fail to create socket. errno = %d, %s", errno, strerror(errno));
        ZOS_FREE(sendMsg);
        return ZCFG_INTERNAL_ERROR;
    }

    // reuse address
    flags = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &flags, sizeof(flags)) < 0)
    {
        ZLOG_ERROR("fail to set socket option SO_REUSEADDR. errno = %d, %s", errno, strerror(errno));
        ZOS_FREE(sendMsg);
        close(fd);
        return ZCFG_INTERNAL_ERROR;
    }

    // nonblocking operation
    flags = fcntl(fd, F_GETFL, 0);
    fcntl(fd, F_SETFL, flags | O_NONBLOCK);

    /* get address for bind() */
    server_addr.sun_family = AF_UNIX;
    addrlen = sizeof(server_addr);

    // get unique sequence ID
    seqid = zos_pid_get();

    _MUTEX_LOCK();
    _zcfg_msg_req_idx = ((_zcfg_msg_req_idx) % 0xFFFF) + 1;
    seqid |= (_zcfg_msg_req_idx << 16);
    _MUTEX_UNLOCK();

    sprintf(server_addr.sun_path, "%s%u-%u", ZCFG_ADDRESS_PREFIX, eid, seqid);

    // bind on address
    if (bind(fd, (struct sockaddr*)&server_addr, addrlen) < 0)
    {
        ZLOG_ERROR("fail to bind address. errno = %d, %s", errno, strerror(errno));
        ZOS_FREE(sendMsg);
        close(fd);
        unlink(server_addr.sun_path);
        return ZCFG_INTERNAL_ERROR;
    }

    ZLOG_DEBUG("EID %u bind server on %s successfully", eid, server_addr.sun_path);

    chmod(server_addr.sun_path, 0777);

    /*
        sendMsg will be freed in _msg_send no matter of result !!!
    */

    // get send information
    send_type = sendMsg->type;
    send_oid  = sendMsg->oid;
    dst_eid   = sendMsg->dstEid;

    // send message
    ret = _msg_send(eid, fd, false, sendMsg);
    if (ret != ZCFG_SUCCESS)
    {
        ZLOG_ERROR("fail to send message. ret = %d", ret);
        close(fd);
        unlink(server_addr.sun_path);
        return ret;
    }

    // Check whether it needs to wait reply message
    if (send_type & ZCFG_NO_WAIT_REPLY)
    {
        close(fd);
        unlink(server_addr.sun_path);

        ZLOG_DEBUG("EID %u not need to wait for reply, close socket", eid);

        return ZCFG_SUCCESS_AND_NO_REPLY;
    }

    // receive message
    ret = _msg_recv(eid, fd, false, replyMsg, timeout_msec, dst_eid, send_type, send_oid);

    if (ret != ZCFG_SUCCESS)
    {
        ZLOG_ERROR("fail to receive message. ret = %d", ret);
    }

    close(fd);
    unlink(server_addr.sun_path);
    return ret;

} // zcfg_msg_sendAndGetReply

/*!
 *  get EID of current thread
 *
 *  @return > 0     successful, valid eid
 *          0       fail
 */
zcfg_msg_eid_t zcfg_msg_eidGet()
{
    _msg_data_s     *my_entry;

    _MUTEX_LOCK();

    my_entry = _my_msg_data_get();

    _MUTEX_UNLOCK();

    /*
        the thread does not register its own EID, then use the one of process
    */
    if (my_entry == NULL)
    {
        ZLOG_ERROR("fail to get my entry");
        return 0;
    }

    return my_entry->eid;
}

/*!
 *  get socket ID of current thread
 *
 *  @return >= 0    successful, valid socket ID
 *          <  0    fail
 */
int zcfg_msg_sckIdGet()
{
    _msg_data_s     *my_entry;

    _MUTEX_LOCK();

    my_entry = _my_msg_data_get();

    _MUTEX_UNLOCK();

    if (my_entry == NULL)
    {
        ZLOG_ERROR("fail to get my entry");
        return 0;
    }

    return my_entry->sck_id;
}

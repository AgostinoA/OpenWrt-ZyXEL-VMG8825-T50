#ifndef _ZCFG_MSG_H_
#define _ZCFG_MSG_H_

#include <stdint.h>

#include "zcfg_common.h"
#include "zcfg_eid.h"
#include "zcfg_msg_type.h"

//==============================================================================
#define ZCFG_ADDRESS_PREFIX     "/var/lib/.sock/zcfg_sockaddr"
#define ZCFG_MSG_BACKLOG        5

//==============================================================================
typedef uint8_t     zcfg_msg_eid_t;

/*
    Notice the alignment
*/
typedef struct zcfgMsg_s
{
	uint32_t        type;
	uint32_t        oid;
	zcfg_msg_eid_t  srcEid;
	zcfg_msg_eid_t  dstEid;
	uint16_t        length;
	uint32_t        clientPid;
	int32_t         statCode;
	char            reserve[28];
	objIndex_t      objIid[1];      // 7 bytes

} zcfgMsg_t;

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
bool zcfg_msg_eidInit(
    zcfg_msg_eid_t      eid,
    char                *module_name
);

/*!
 *  Initialize a server socket per thread to wait for messages from others.
 *
 *  @return ZCFG_SUCCESS    successful
 *          others          fail
 */
zcfgRet_t zcfg_msg_serverInit();

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
zcfgRet_t zcfg_msg_serverRecv(
    zcfgMsg_t   **recvBuf,
    uint32_t    timeout_msec
);

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
zcfgRet_t zcfg_msg_serverSend(
    zcfgMsg_t   *sendMsg
);

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
zcfgRet_t zcfg_msg_sendAndGetReply(
    zcfgMsg_t   *sendMsg,
    zcfgMsg_t   **replyMsg,
    uint32_t    timeout_msec
);

/*!
 *  get EID of current thread
 *
 *  @return > 0     successful, valid eid
 *          0       fail
 */
zcfg_msg_eid_t zcfg_msg_eidGet();

/*!
 *  get socket ID of current thread
 *
 *  @return >= 0    successful, valid socket ID
 *          <  0    fail
 */
int zcfg_msg_sckIdGet();

//==============================================================================
#define ZCFG_MSG_INVALID_EID(_eid_)             ((_eid_) <= 0 || (_eid_) >= ZCFG_EID_MAX)

#define ZCFG_MSG_WAIT_FOREVER                   0
#define ZCFG_MSG_WAIT_NONE                      0xFFffFFff

#define zcfgEidInit(_e_, _m_)                   zcfg_msg_eidInit(_e_, _m_)
#define zcfgMsgServerInit()                     zcfg_msg_serverInit()
#define zcfgMsgReqRecv(_r_, _t_)                zcfg_msg_serverRecv(_r_, _t_)
#define zcfgMsgRepSend(_s_)                     zcfg_msg_serverSend(_s_)
#define zcfgMsgSendAndGetReply(_s_, _r_, _t_)   zcfg_msg_sendAndGetReply(_s_, _r_, _t_)

#if 0
#define zcfg_msg_dbg_printf(_fmt_, ...) \
    fprintf(stderr, "[PID %u] %s line %d, %s(), " _fmt_, zcfg_msg_pid_get(), __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#endif

//==============================================================================
#endif // _ZCFG_MSG_H_

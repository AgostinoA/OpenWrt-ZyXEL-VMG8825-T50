#ifndef _ZOS_API_H
#define _ZOS_API_H
//==============================================================================
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "zlog_api.h"

//==============================================================================
#define ZOS_MAX_PROCESS_TIME       2000 // milli-second

//==============================================================================
/*
    Public MACRO
*/
#define ZOS_MALLOC(_size_) \
    ({\
        void *_p_ = NULL; \
        do \
        { \
            _p_ = calloc(1, (size_t)(_size_)); \
            if (_p_ == NULL) \
            { \
                ZLOG_ERROR("fail to calloc memory, size = %zu", (size_t)(_size_)); \
            } \
        } \
        while (0); \
        _p_; \
    })

#define ZOS_FREE(_p_) \
    {\
        do \
        { \
            if ((_p_) == NULL) \
            { \
                ZLOG_DEBUG("Free NULL pointer"); \
            } \
            else \
            { \
                free((void *)(_p_)); \
                (_p_) = NULL; \
            } \
        } \
        while (0); \
    }

/*
    use system()
*/
#define ZOS_SYSTEM(_fmt_, ...) \
    ({ \
        bool    zb = zos_system(true, _fmt_, ##__VA_ARGS__); \
        if (zb == false) \
        { \
            ZLOG_ERROR("fail to run system()"); \
        } \
        zb; \
    })

/*
    use zcfg_system() for security
*/
#define ZOS_SYSTEM_S(_fmt_, ...) \
    ({ \
        bool    zb = zos_system(false, _fmt_, ##__VA_ARGS__); \
        if (zb == false) \
        { \
            ZLOG_ERROR("fail to run system()"); \
        } \
        zb; \
    })

//==============================================================================
/*!
 *  system command
 *
 *  @param [in] b_linux     if true then use linux system() else use _zcfg_system()
 *  @param [in] format      string format of command
 *  @param [in] ...         arguments required by the format
 *
 *  @return true  - command executed successful
 *          false - fail to execute command
 */
bool zos_system(
    bool        b_linux,
    const char  *format,
    ...
);

/*!
 *  work as snprintf(), avoid the issue from man page
 *      "However, the standards explicitly note that the results are undefined
 *      if source and destination buffers overlap when calling sprintf(),
 *      snprintf(), vsprintf(), and vsnprintf()."
 *
 *  @param [in] buf          string buffer to print to
 *  @param [in[ size         maximum size of the string
 *  @param [in] format       string format of command
 *  @param [in] ...          arguments required by the format
 *
 *  @return >= 0 - successful, the number of characters printed
 *          <  0 - failed
 */
int zos_snprintf(
    char        *buf,
    size_t      size,
    const char  *format,
    ...
);

/*!
 *  get my pid which is shown in top command.
 *
 *  @return uint32_t      my pid
 */
uint32_t zos_pid_get();

/*!
 *  get monotonic time in milli-second.
 *
 *  @return uint32_t    milli-second
 *                      0: failed
 */
uint32_t zos_mtime_get();

//==============================================================================
#endif /* _ZOS_API_H */

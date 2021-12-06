/*!
 *  @file zlog_api.c
 *      library of syslog-ng
 *
 *  @author     CP Wang
 *  @date       2017-12-12 18:38:46
 *  @copyright  Copyright 2017 Zyxel Communications Corp. All Rights Reserved.
 */
//==============================================================================
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <sys/types.h>
#include <syslog.h>
#include <stdarg.h>
#include <stdint.h>

#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <unistd.h>         // for syscall()
#include <sys/syscall.h>    // for syscall()

#include "zlog_api.h"

#include <errno.h>          // for program_invocation_short_name
extern char *program_invocation_short_name;

//==============================================================================
/*
    0 - printf()
    1 - syslog-ng
*/
#ifdef CONFIG_ZLOG_USE_DEBUG

#define _USE_SYSLOG     1

#else

#define _USE_SYSLOG     0

#endif 

/*
    --- IMPORTANT ---
        this macro is to break the circular dependency with zos
        this should always be the same as zos_pid_get()
*/
#define _pid_get()      (uint32_t)(syscall(__NR_gettid))

#define _dbg_printf(_fmt_, ...) \
    fprintf(stderr, "[PID %u] %s line %d, %s(), " _fmt_, _pid_get(), __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)

//==============================================================================
static zlog_level_t     _log_level = ZLOG_LEVEL_INFO;
static zlog_faci_t      _facility  = ZLOG_FACI_USER;

//==============================================================================
#if 0
static const char *_faci_str(
    zlog_faci_t     facility
)
{
    switch (facility)
    {
        case ZLOG_FACI_USER:    return "user";
        case ZLOG_FACI_KERNEL:  return "kernel";
        default:                return "unknown";
    }
}
#endif

static const char *_level_str(
    zlog_level_t    level
)
{
    switch (level)
    {
        case ZLOG_LEVEL_EMERG:      return "EMERG";
        case ZLOG_LEVEL_ALERT:      return "ALERT";
        case ZLOG_LEVEL_CRITICAL:   return "CRITICAL";
        case ZLOG_LEVEL_ERROR:      return "ERROR";
        case ZLOG_LEVEL_WARNING:    return "WARNING";
        case ZLOG_LEVEL_NOTICE:     return "NOTICE";
        case ZLOG_LEVEL_INFO:       return "INFO";
        case ZLOG_LEVEL_DEBUG:      return "DEBUG";
        default:                    return "UNKNOWN";
    }
}

/*!
 *  get string of date time
 *
 *  @param [out] str    string buffer to get date time.
 *                      The buffer size must be >= 20.
 *
 *  @return true  - successful
 *          false - failed
 */
static bool _datetime_str(
    char    *str
)
{
    int         r;
    time_t      now = time(0);
    struct tm   result;
    struct tm*  ltm = localtime_r(&now, &result);

    if (ltm == NULL)
    {
        return false;
    }

    r = sprintf(str, "%04d-%02d-%02d %02d:%02d:%02d", 1900 + ltm->tm_year, 1 + ltm->tm_mon,
                ltm->tm_mday, ltm->tm_hour, ltm->tm_min, ltm->tm_sec);

    if (r <= 0)
    {
        return false;
    }

    return true;
}

//==============================================================================
/*!
 *  opens a connection to the system logger for a program
 *
 *  @param [in] module_name     module name.  If NULL, the program name is used.
 *  @param [in] facility        log facility
 *
 *  @return true  - successful
 *          false - failed
 */
bool zlog_open(
    char            *module,
    zlog_faci_t     facility
)
{
    int     ng_facility;

    switch (facility)
    {
        case ZLOG_FACI_USER:
            ng_facility = LOG_USER;
            break;

        case ZLOG_FACI_KERNEL:
            ng_facility = LOG_KERN;
            break;

        default:
            _dbg_printf("ERROR : invalid facility %d\n", facility);
            return false;
    }

    _facility = facility;

#if 1
    openlog(module, LOG_NOWAIT | LOG_NDELAY, ng_facility);
#else
    /* output to console */
    openlog(module, LOG_NOWAIT | LOG_NDELAY | LOG_PERROR, ng_facility);
#endif

    return true;
}

/*!
 *  generates a log message
 *
 *  @param [in] level   log level
 *  @param [in] file    C file name
 *  @param [in] line    line of the code
 *  @param [in] func    API name
 *  @param [in] format  string format of log message
 *  @param [in] ...     any arguments required by the format
 *
 *  @note   no return value, reasons are
 *          1. nothing can do it fail
 *          2. if fail, the error message will pop up automatically
 */
void zlog_log_f(
    const zlog_level_t      level,
    const char              *file,
    const int               line,
    const char              *func,
    const char              *format,
    ...
)
{
#define _STR_MAX_LEN    256
#define _MSG_MAX_LEN    (_STR_MAX_LEN * 2)

    char        str[_STR_MAX_LEN + 1] = {0};
    char        msg[_MSG_MAX_LEN + 1] = {0};
    char        date[20]              = {0};
    int         r;
    va_list     ap;

    memset(str,  0, sizeof(str));
    memset(msg,  0, sizeof(msg));
    memset(date, 0, sizeof(date));

#if _USE_SYSLOG

    int         priority;

    switch (level)
    {
        case ZLOG_LEVEL_EMERG:
            priority = LOG_EMERG;
            break;

        case ZLOG_LEVEL_ALERT:
            priority = LOG_ALERT;
            break;

        case ZLOG_LEVEL_CRITICAL:
            priority = LOG_CRIT;
            break;

        case ZLOG_LEVEL_ERROR:
            priority = LOG_ERR;
            break;

        case ZLOG_LEVEL_WARNING:
            priority = LOG_WARNING;
            break;

        case ZLOG_LEVEL_NOTICE:
            priority = LOG_NOTICE;
            break;

        case ZLOG_LEVEL_INFO:
            priority = LOG_INFO;
            break;

        case ZLOG_LEVEL_DEBUG:
            priority = LOG_DEBUG;
            break;

        default:
            _dbg_printf("ERROR : invalid level %d\n", level);
            return ;
    }

#else // _USE_SYSLOG

    if (level < 0 || level > ZLOG_LEVEL_DEBUG)
    {
        _dbg_printf("ERROR : invalid level %d\n", level);
        return;
    }

#endif // _USE_SYSLOG

    if (_datetime_str(date) == false)
    {
        _dbg_printf("fail to get date time\n");
        return;
    }

    if (format == NULL)
    {
        _dbg_printf("format == NULL\n");
        return;
    }

    va_start(ap, format);

    r = vsnprintf(str, _STR_MAX_LEN, format, ap);

    va_end(ap);

    if (r < 0 || r > _STR_MAX_LEN)
    {
        _dbg_printf("fail to vsnprintf()\n");
        return;
    }

    // remove tailing '\n'
    r = strlen(str);
    if (r > 0 && r <= _STR_MAX_LEN)
    {
        if (str[r - 1] == '\n' || str[r - 1] == '\r')
        {
            str[r - 1] = 0;
        }
    }

    if (file)
    {
        /*
            <time> <program><<pid>, <file>:<line> <func> <severity> : <message>
        */
        r = snprintf(msg, _MSG_MAX_LEN, "%s %s<%u>, %s:%d, %s(), %s: %s\n", date,
                     program_invocation_short_name, _pid_get(), file,
                     line, func, _level_str(level), str);

        if (r < 0)
        {
            _dbg_printf("fail to snprintf()\n");
            return;
        }
    }
    else
    {
        /*
            <time> <program><<pid>, <severity> : <message>
        */
        r = snprintf(msg, _MSG_MAX_LEN, "%s %s<%u>, %s: %s\n", date,
                     program_invocation_short_name, _pid_get(),
                     _level_str(level), str);

        if (r < 0)
        {
            _dbg_printf("fail to snprintf()\n");
            return;
        }
    }

#if _USE_SYSLOG

    syslog(priority, "%s", msg);

#else // _USE_SYSLOG

    printf("%s", msg);

#endif // _USE_SYSLOG

    return;

} // zlog_log_f

/*!
 *  set log level to filter the logs
 *
 *  @param [in] level   log level
 *
 *  @return true  - successful
 *          false - failed
 */
bool zlog_levelSet(
    const zlog_level_t  level
)
{
    if (level < 0 || level > ZLOG_LEVEL_DEBUG)
    {
        _dbg_printf("ERROR : invalid level %d\n", level);
        return false;
    }

    _log_level = level;
    return true;
}

/*!
 *  get current log level
 *
 *  @return current log level
 */
zlog_level_t zlog_levelGet()
{
    return _log_level;
}

/*!
 *  check if the log level is allowed
 *
 *  @param [in] level   log level
 *
 *  @return true  - the level is allowed
 *          false - the level is denied
 */
bool zlog_levelAllow(
    const zlog_level_t  level
)
{
    if (level < 0 || level > _log_level)
    {
        return false;
    }

    return true;
}

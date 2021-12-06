#ifndef _ZLOG_API_H_
#define _ZLOG_API_H_
//==============================================================================
#include <stdbool.h>

//==============================================================================
typedef enum
{
    ZLOG_FACI_USER,     // user space application
    ZLOG_FACI_KERNEL    // kernel space daemon
} zlog_faci_t;

typedef enum
{
    ZLOG_LEVEL_EMERG = 0,
    ZLOG_LEVEL_ALERT,
    ZLOG_LEVEL_CRITICAL,
    ZLOG_LEVEL_ERROR,
    ZLOG_LEVEL_WARNING,
    ZLOG_LEVEL_NOTICE,
    ZLOG_LEVEL_INFO,
    ZLOG_LEVEL_DEBUG
} zlog_level_t;

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
);

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
);

/*!
 *  generates a log message
 *
 *  @param [in] level   log level
 *  @param [in] format  string format of log message
 *  @param [in] ...     any arguments required by the format
 *
 *  @return true  - successful
 *          false - failed
 */
bool zlog_log(
    zlog_level_t    level,
    const char      *format,
    ...
);

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
);

/*!
 *  get current log level
 *
 *  @return current log level
 */
zlog_level_t zlog_levelGet();

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
);

//==============================================================================
/*
    The macro is for internal use
*/
#define _ZLOG_MSG(_level_, _fmt_, ...) \
{\
    if (zlog_levelAllow(_level_)) {\
        zlog_log_f(_level_, __FILE__, __LINE__, __FUNCTION__, _fmt_, ##__VA_ARGS__);\
    }\
}

//==============================================================================
/*
    Public macro
*/
#define ZLOG_EMERG(_fmt_, ...)     _ZLOG_MSG(ZLOG_LEVEL_EMERG,    _fmt_, ##__VA_ARGS__)
#define ZLOG_ALERT(_fmt_, ...)     _ZLOG_MSG(ZLOG_LEVEL_ALERT,    _fmt_, ##__VA_ARGS__)
#define ZLOG_CRITICAL(_fmt_, ...)  _ZLOG_MSG(ZLOG_LEVEL_CRITICAL, _fmt_, ##__VA_ARGS__)
#define ZLOG_ERROR(_fmt_, ...)     _ZLOG_MSG(ZLOG_LEVEL_ERROR,    _fmt_, ##__VA_ARGS__)
#define ZLOG_WARNING(_fmt_, ...)   _ZLOG_MSG(ZLOG_LEVEL_WARNING,  _fmt_, ##__VA_ARGS__)
#define ZLOG_NOTICE(_fmt_, ...)    _ZLOG_MSG(ZLOG_LEVEL_NOTICE,   _fmt_, ##__VA_ARGS__)
#define ZLOG_INFO(_fmt_, ...)      _ZLOG_MSG(ZLOG_LEVEL_INFO,     _fmt_, ##__VA_ARGS__)
#define ZLOG_DEBUG(_fmt_, ...)     _ZLOG_MSG(ZLOG_LEVEL_DEBUG,    _fmt_, ##__VA_ARGS__)
//==============================================================================
#endif // _ZLOG_API_H_

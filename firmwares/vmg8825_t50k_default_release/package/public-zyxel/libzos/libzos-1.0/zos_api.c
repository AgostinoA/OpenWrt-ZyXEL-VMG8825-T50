/*!
 *  @file zos_api.c
 *      OS porting layer
 *
 *  @author     CP Wang
 *  @date       2017-12-15 19:26:21
 *  @copyright  Copyright 2017 Zyxel Communications Corp. All Rights Reserved.
 */
//==============================================================================
#include <stdio.h>
#include <stdlib.h>     // system()
#include <stdarg.h>     // va_list()
#include <sys/types.h>
#include <sys/wait.h>   // waitpid()
#include <string.h>     // strchr()
#include <errno.h>
#include <time.h>
#include <stdint.h>

#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <unistd.h>         // for syscall(), fork(), execvp(), _exit()
#include <sys/syscall.h>    // for syscall()

#include "zos_api.h"
#include "zlog_api.h"

//==============================================================================
#define ZOS_CMD_MAX_LEN     1024

//==============================================================================
/*
    copy from
        build_dir\target-arm_v7-a_uClibc-0.9.32_eabi\zcfg_be-2.0\libzcfg_be\libzcfg_be_common\zcfg_be_common.c
*/
/*
 * zcfg_system():
 * Used to prevent command injection
 * usage likes system(), but does not support sepcial characters except & "
 * & must be seperate and can not be appended to the parameters
 * e.g.
 * Correct case : zcfg_system("ping 8.8.8.8 &") -> excute "ping 8.8.8.8" in background
 * Wrong case : zcfg_system("ping 8.8.8.8&")  -> 8.8.8.8& will be treate as a argement
 *
 * zcfg_system("ping \"8.8.8.8 4.4.4.4\"")  -> 8.8.8.8 4.4.4.4 will be treate as a argement since they are enclosed in double quotation marks
 * zcfg_system("ping 8.8.8.8 > /tmp/result)  -> not support redirect (>)
 *
 * plan to support redirect (>) in future.
 */
static int _zcfg_system(const char *cmd)
{
	pid_t pid;
	pid_t pid2;
	char  *argv[128] = {NULL};
	char  buf[ZOS_CMD_MAX_LEN + 1] = {0};
	int   i = 0;
	int   j = 0;
	char  *p = NULL;
	int   status = 0;
	int   background = 0;

	if (*cmd == '\0')
	{
		return -1;
	}

	strncpy(buf, cmd, ZOS_CMD_MAX_LEN);

	while (i<ZOS_CMD_MAX_LEN && cmd[i]!='\0')
	{
		if(buf[i] != ' '){
			if(buf[i] == '\"'){
				argv[j++] = &buf[++i];
				p = strchr(&buf[i], '\"');
				if(p != NULL){
					i = p - buf;
					buf[i] = '\0';
				}
				else
					return -1;

			}
			else{
				argv[j++] = &buf[i];
				p = strchr(&buf[i], ' ');
				if(p != NULL){
					i = p - buf;
					buf[i] = '\0';
				}
				else
					break;
			}
		}
		i++;
	}

	if (*argv[j-1] == '&')
        {
		background = 1;
		argv[j-1] = NULL;
	}

	if ((pid = fork()) < 0)
        {
		status = -1;
	}
	else if (pid == 0)
        {
		if(!background){
			execvp(argv[0], argv);
			_exit(127);
		}
		else{
			if((pid2 = fork()) < 0){
				_exit(-1);
			}
			else if(pid2 == 0){
				execvp(argv[0], argv);
				_exit(127);
			}
			else{
				_exit(0);
			}
		}
	}
	else if(pid >0){
		if(waitpid(pid, &status, 0)<0){
			if (errno != EINTR) {
				status = -1;
			}
		}
	}

	return status;

} // _zcfg_system

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
)
{
    char        cmd[ZOS_CMD_MAX_LEN + 1] = {0};
    va_list     ap;
    int         r;

    memset(cmd, 0, sizeof(cmd));

    if (format == NULL)
    {
        ZLOG_ERROR("format == NULL");
        return false;
    }

    va_start(ap, format);

    r = vsnprintf(cmd, ZOS_CMD_MAX_LEN, format, ap);

    va_end(ap);

    if (r < 0 || r > ZOS_CMD_MAX_LEN)
    {
        ZLOG_ERROR("fail to vsnprintf()");
        return false;
    }

    if (b_linux)
    {
        if (system(cmd) == -1)
        {
            ZLOG_ERROR("fail to system(%s)", cmd);
            return false;
        }
    }
    else
    {
        if (_zcfg_system(cmd) == -1)
        {
            ZLOG_ERROR("fail to _zcfg_system(%s)", cmd);
            return false;
        }
    }

    return true;

} // zos_system

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
)
{
    char        *tmp_buf;
    va_list     arg;
    int         ret = -1;

    if (buf == NULL)
    {
        ZLOG_ERROR("buf == NULL");
        return ret;
    }

    if (format == NULL)
    {
        ZLOG_ERROR("format == NULL");
        return ret;
    }

    tmp_buf = ZOS_MALLOC(size);
    if (tmp_buf == NULL)
    {
        ZLOG_ERROR("fail to allocate memory");
        return ret;
    }

    va_start(arg, format);
    ret = vsnprintf(tmp_buf, size, format, arg);
    va_end(arg);

    if (ret >= 0)
    {
        memset(buf, 0, size);

        if (ret > 0)
        {
            strcpy(buf, tmp_buf);
        }
    }

    ZOS_FREE(tmp_buf);

    return ret;

} // zos_snprintf

/*!
 *  get my pid which is shown in top command.
 *
 *  @return uint32_t      my pid
 */
uint32_t zos_pid_get()
{
    return (uint32_t)(syscall(__NR_gettid));
}

/*!
 *  get monotonic time in milli-second.
 *
 *  @return uint32_t    milli-second
 *                      0: failed
 */
uint32_t zos_mtime_get()
{
    struct timespec     tp;

    if (clock_gettime(CLOCK_MONOTONIC, &tp) != 0)
    {
        ZLOG_ERROR("fail to get monotonic time");
        return 0;
    }

    return tp.tv_sec * 1000 + tp.tv_nsec / 1000000;
}




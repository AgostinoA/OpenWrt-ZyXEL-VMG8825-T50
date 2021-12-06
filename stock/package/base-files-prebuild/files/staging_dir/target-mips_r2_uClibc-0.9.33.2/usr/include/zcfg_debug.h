#ifndef _ZCFG_DEBUG_H
#define _ZCFG_DEBUG_H

#include <syslog.h>

#define ZCFG_LOG_USE_SYSLOG 1

#ifdef ZCFG_LOG_USE_DEBUGCFG
#undef ZCFG_LOG_USE_SYSLOG
#endif

#ifndef ZCFG_MSG_DEBUGCFG
extern struct json_object *myDebugCfgObj __attribute__((weak));
extern unsigned int myDebugCfgObjLevel __attribute__((weak));
#endif

/*ZCFG debug level*/
#define ZCFG_LOG_EMERG   LOG_EMERG
#define ZCFG_LOG_ALERT   LOG_ALERT
#define ZCFG_LOG_CRIT    LOG_CRIT
#define ZCFG_LOG_ERR     LOG_ERR
#define ZCFG_LOG_WARNING LOG_WARNING
#define ZCFG_LOG_NOTICE  LOG_NOTICE
#define ZCFG_LOG_INFO    LOG_INFO
#define ZCFG_LOG_DEBUG   LOG_DEBUG
/*End*/

/*ZCFG LOG Prefix*/
#define ZCFG_LOGPRE_ACCOUNT "Account:"
#define ZCFG_LOGPRE_XDSL "xDSL:"
#define ZCFG_LOGPRE_IGMP "IGMP:"
#define ZCFG_LOGPRE_ACL "ACL:"
#define ZCFG_LOGPRE_WIFI "Wifi:"
#define ZCFG_LOGPRE_NAT "NAT:"
#define ZCFG_LOGPRE_QOS "QoS:"
#define ZCFG_LOGPRE_DDNS "DDNS:"
#define ZCFG_LOGPRE_MACFILTER "MACFilter:"
#define ZCFG_LOGPRE_FIREWALL "Firewall:"
#define ZCFG_LOGPRE_SYSTEM "System:"
#define ZCFG_LOGPRE_UPNP "upnp:"

/*End*/

/*Log the message of level less than ZCFG_LOG_LEVEL*/
#define ZCFG_LOG_LEVEL ZCFG_LOG_INFO

#if ZCFG_LOG_USE_SYSLOG
#define zcfgLog(logLev, format, ...) \
                if(ZCFG_LOG_LEVEL >= logLev) \
                        syslog(logLev, format, ##__VA_ARGS__)
#define zcfgLogPrefix(logLev, Prefix, format, ...) \
                if(ZCFG_LOG_LEVEL >= logLev) \
                        syslog(logLev, Prefix " " format, ##__VA_ARGS__)
#elif defined(ZCFG_LOG_USE_DEBUGCFG)

#define ZCFG_DEBUGCFG_SYSLOG (1 << 3)
#define ZCFG_DEBUGCFG_STDLOG (1 << 4)
#define ZCFG_DEBUGCFG_LOGLEVMASK ((1 << 3)-1)
#define ZCFG_DEBUGCFG_OPTIONMASK (((1 << 16)-1) << 8)  // additional debug options mask

enum {
        ZCFG_SL_EMERG =  ZCFG_LOG_EMERG | ZCFG_DEBUGCFG_SYSLOG,
        ZCFG_SL_ALERT =  ZCFG_LOG_ALERT | ZCFG_DEBUGCFG_SYSLOG,
        ZCFG_SL_CRIT =   ZCFG_LOG_CRIT | ZCFG_DEBUGCFG_SYSLOG,
        ZCFG_SL_ERR  =   ZCFG_LOG_ERR | ZCFG_DEBUGCFG_SYSLOG,
        ZCFG_SL_WARNING = ZCFG_LOG_WARNING | ZCFG_DEBUGCFG_SYSLOG,
        ZCFG_SL_NOTICE = ZCFG_LOG_NOTICE | ZCFG_DEBUGCFG_SYSLOG,
        ZCFG_SL_INFO  =  ZCFG_LOG_INFO | ZCFG_DEBUGCFG_SYSLOG,
        ZCFG_SL_DEBUG =  ZCFG_LOG_DEBUG | ZCFG_DEBUGCFG_SYSLOG,
        ZCFG_DL_EMERG =  ZCFG_LOG_EMERG | ZCFG_DEBUGCFG_STDLOG,
        ZCFG_DL_ALERT =  ZCFG_LOG_ALERT | ZCFG_DEBUGCFG_STDLOG,
        ZCFG_DL_CRIT =   ZCFG_LOG_CRIT | ZCFG_DEBUGCFG_STDLOG,
        ZCFG_DL_ERR  =   ZCFG_LOG_ERR | ZCFG_DEBUGCFG_STDLOG,
        ZCFG_DL_WARNING = ZCFG_LOG_WARNING | ZCFG_DEBUGCFG_STDLOG,
        ZCFG_DL_NOTICE = ZCFG_LOG_NOTICE | ZCFG_DEBUGCFG_STDLOG,
        ZCFG_DL_INFO  =  ZCFG_LOG_INFO | ZCFG_DEBUGCFG_STDLOG,
        ZCFG_DL_DEBUG =  ZCFG_LOG_DEBUG | ZCFG_DEBUGCFG_STDLOG,
        ZCFG_SDL_EMERG =  ZCFG_LOG_EMERG | ZCFG_DEBUGCFG_SYSLOG | ZCFG_DEBUGCFG_STDLOG,
        ZCFG_SDL_ALERT =  ZCFG_LOG_ALERT | ZCFG_DEBUGCFG_SYSLOG | ZCFG_DEBUGCFG_STDLOG,
        ZCFG_SDL_CRIT =   ZCFG_LOG_CRIT | ZCFG_DEBUGCFG_SYSLOG | ZCFG_DEBUGCFG_STDLOG,
        ZCFG_SDL_ERR  =   ZCFG_LOG_ERR | ZCFG_DEBUGCFG_SYSLOG | ZCFG_DEBUGCFG_STDLOG,
        ZCFG_SDL_WARNING = ZCFG_LOG_WARNING | ZCFG_DEBUGCFG_SYSLOG | ZCFG_DEBUGCFG_STDLOG,
        ZCFG_SDL_NOTICE = ZCFG_LOG_NOTICE | ZCFG_DEBUGCFG_SYSLOG | ZCFG_DEBUGCFG_STDLOG,
        ZCFG_SDL_INFO  =  ZCFG_LOG_INFO | ZCFG_DEBUGCFG_SYSLOG | ZCFG_DEBUGCFG_STDLOG,
        ZCFG_SDL_DEBUG =  ZCFG_LOG_DEBUG | ZCFG_DEBUGCFG_SYSLOG | ZCFG_DEBUGCFG_STDLOG
};


#define zsyslog(logLev, format, ...) \
              { if(((myDebugCfgObjLevel & ZCFG_DEBUGCFG_SYSLOG) || (logLev & ZCFG_DEBUGCFG_SYSLOG)) \
                   && ((myDebugCfgObjLevel & ZCFG_DEBUGCFG_LOGLEVMASK) >= (logLev & ZCFG_DEBUGCFG_LOGLEVMASK))) \
                    syslog((logLev & ZCFG_DEBUGCFG_LOGLEVMASK), format, ##__VA_ARGS__); }

#define zstdlog(logLev, format, ...) \
              { if(((myDebugCfgObjLevel & ZCFG_DEBUGCFG_STDLOG) || (logLev & ZCFG_DEBUGCFG_STDLOG)) \
                   && ((myDebugCfgObjLevel & ZCFG_DEBUGCFG_LOGLEVMASK) >= (logLev & ZCFG_DEBUGCFG_LOGLEVMASK))) \
                    printf(format, ##__VA_ARGS__); }

#ifdef ZCFG_ZYUTIL_DEBUG_API  // static api
void zcfgDebug(int , const char *,...);
#define zcfgLog(logLev, format, ...) zcfgDebug(logLev, format, ##__VA_ARGS__)
#define zcfgLogPrefix(logLev, PreFix, format, ...) zcfgDebug(logLev, PreFix " " format, ##__VA_ARGS__)
#elif ZCFG_ZYUTIL_DYNAMIC_DEBUG_API
void zyUtilDebug(int , const char *,...);
#define zcfgLog(logLev, format, ...) zyUtilDebug(logLev, format, ##__VA_ARGS__)
#define zcfgLogPrefix(logLev, PreFix, format, ...) zyUtilDebug(logLev, PreFix " " format, ##__VA_ARGS__)
#else
#define zcfgLog(logLev, format, ...) {if(myDebugCfgObj){\
		zsyslog(logLev, format, ##__VA_ARGS__); \
		zstdlog(logLev, format, ##__VA_ARGS__); \
	}else if(ZCFG_LOG_LEVEL >= logLev){syslog(logLev, format, ##__VA_ARGS__);}}

#define zcfgLogPrefix(logLev, PreFix, format, ...) {if(myDebugCfgObj){\
		zsyslog(logLev, PreFix " " format, ##__VA_ARGS__); \
		zstdlog(logLev, PreFix " " format, ##__VA_ARGS__); \
	}else if(ZCFG_LOG_LEVEL >= logLev){syslog(logLev, PreFix " " format, ##__VA_ARGS__);}}
#endif

#else
#define zcfgLog(logLev, format, ...) \
		if(ZCFG_LOG_LEVEL >= logLev) \
			printf(format, ##__VA_ARGS__)
#define zcfgLogPrefix(logLev, Prefix, format, ...) \
                if(ZCFG_LOG_LEVEL >= logLev) \
                        printf(Prefix " " format, ##__VA_ARGS__)
#endif


#endif

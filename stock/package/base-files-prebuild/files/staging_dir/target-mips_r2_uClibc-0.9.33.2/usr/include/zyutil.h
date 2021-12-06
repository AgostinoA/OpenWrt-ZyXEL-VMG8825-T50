#ifndef _ZCFG_UTIL_H
#define _ZCFG_UTIL_H

#include "libzyutil_wrapper.h"

#define MAC_STR_LEN     17
#define MAC_ADDR_LEN    6
#define SERIAL_NUM_STR_LEN  13

/*Common*/
void zyUtilIfaceHwAddrGet(char *, char *);
bool zyUtilIsAppRunning(char *);
bool zyUtilCheckIfaceUp(char *);
void zyUtilAddIntfToBridge(char *, char *);
void zyUtilDelIntfFromBridge(char *, char *);
void zyUtilStrReplace (char *source, char* find_str, char*rep_str);
void zyUtilBackslashInsert(char *);
void zyUtilBackslashInForEcho(char *);
int32_t zyUtilOidGet(const char *objNameAbbr);

zcfgRet_t zyUtilIGetBaseMACwithColon(char *mac);
zcfgRet_t zyUtilMacStrToNum(const char *, uint8_t *);
zcfgRet_t zyUtilMacNumToStr(const uint8_t *, char *);
int zyUtilGetGPIO(int gpioNum);
/*DNS*/
zcfgRet_t zyUtilGetDomainNameFromUrl(char *, char *, int);

/*Flash*/
zcfgRet_t zyUtilMtdDevGetByName(char *mtdname, char *mtddev);
unsigned int zyUtilMtdDevGetSize(char *devName);
zcfgRet_t zyUtilWriteBufToFlash(char *devName, void *buf, uint32_t buf_size);
int zyUtilReadBufFromFlash(char *devName, void *buf, uint32_t buf_size);
#if 1 //#ifdef ZYXEL_WWAN
int zyUtilMtdErase(const char *mtd);
int zyUtilUpdateWWANPackage(void);
#define ZY_WWANPACKAGE_MAXSIZE	131072  // (1024*128) bytes
#define WWANPACKAGE_HEADER_LEN	32  // theoretically speaking 31 is match
#define FW_WWANPACKAGE_FILE	"/etc/fw_wwanpackage"
#define RUN_WWANPACKAGE_FILE	"/var/wwan/run_wwanpackage"
#endif
zcfgRet_t zyUtilAppStopByPidfile(char *);

zcfgRet_t zyUtilMailSend(const char *msg);


bool zyUtilRetrieveSystemDefaultRoutIface(char *interfaceName);
zcfgRet_t zyUtilValidIpAddr(const char *);
int zyUtilIp4AddrDomainCmp(const char *, const char *, const char *);
#define SYSTEM_UUID_PATH       "/proc/sys/kernel/random/uuid"
zcfgRet_t zyUtilIGetBridgeIPAddr(char *ipAddress);
zcfgRet_t zyUtilIGetUPnPuuid(char *uuid);

bool zyUtilFileExists(const char * filename);


int zyUtilQueryUtilityEid(const char *name);

char *zyUtilStrCsvString(const char *, const char *);
void zyUtilStrCsvAppend(char **, const char *);
char *zyUtilCsvStringStripTerm(const char *, const char *);

#ifdef ZYXEL_DETECT_PRODUCT_TYPE
int zyUtilAskBoardFeaturesStringBits(char *, int );
int zyUtilAskProductName(char *prname, int prnameLen);
int zyUtilAskBoardDslSupport(const char *);
int zyUtilAskBoardVoIPSupport(const char *);
#else
#define zyUtilAskBoardFeaturesStringBits(bits, bitsLen) (-1)
#define zyUtilAskProductName(prname, prnameLen) (-1)
#define zyUtilAskBoardDslSupport(bits) (0)
#define zyUtilAskBoardVoIPSupport(bits) (0)
#endif

zcfgRet_t zyUtilHandleRecvdMsgDebugCfg(const char *msg);
unsigned int zcfgMsgDebugCfgLevel(void);
void zcfgMsgDebugCfgLevelSet(unsigned int debugCfgLevel);

//compare routine type define
//parameters:
// void *array: sorted array[]
// int index: indexing an array node to compare
// void *value: a value as index to search
// void **unit: picked array unit, while returning result equal
//
// return: == 0, equal, > 0, not equal, < 0, not equal
typedef int (*compRout)(void *array, int index , void *value, void **unit);
void *zyUtilSortedArraySearch(void *array, compRout cr, void *value, int l, int r);


/* skconn */
#include <sys/un.h>
#include <arpa/inet.h>
#include <sys/time.h>

#define TCP_BACKLOG  5

typedef struct skconn_s
{
   int domain;
   int type;
   int st;
   int fcntl;
   in_addr_t ip; //uint32_t
   unsigned short port;
   char pad[2];
}skconn_t;

unsigned int zyUtilComputeMicroInterval(struct timeval *, struct timeval *);
void zyUtilMakeTimeStamp(struct timeval *tv, char *timeStamp, unsigned int timeStampSz);
int zyUtilTcpConnInit(const int domain, const char *addr, const int port, skconn_t *skconn);
int zyUtilTcpSvrInit(const int domain, const char *addr, const int port, skconn_t *skconn);
int zyUtilUdpConnInit(const int domain, const char *addr, const int port, skconn_t *skconn);
int zyUtilUdpSvrInit(const int domain, const char *addr, const int port, skconn_t *skconn);

//#define ZCFG_IPTABLES_SEM_KEY 1234
#define zyUtilRestoreIptCfg(ipt) zyUtilRestoreIptablesConfig(ipt, __FILE__, __FUNCTION__, __LINE__)

typedef struct
{
	FILE *fp_m; //v4 mangle table
	FILE *fp_f; //v4 filter table
	FILE *fp_n; //v4 nat table
	FILE *fp_m6; //v6 mangle table
	FILE *fp_f6; //v6 filter table
	char *buf_m;
	char *buf_f;
	char *buf_n;
	char *buf_m6;
	char *buf_f6;
	size_t len_m;
	size_t len_f;
	size_t len_n;
	size_t len_m6;
	size_t len_f6;
}iptCfg_t;

bool zyUtilInitIptablesConfig(iptCfg_t **ipt);
void zyUtilRestoreIptablesConfig(iptCfg_t *ipt, const char *file, const char *func, int line);
//void zyUtilIptablesLockInit(void);
//void zyUtilIptablesLock(void);
//void zyUtilIptablesUnLock(void);

int zyUtilAuthUserAccount(const char *username, const char *password);
char *zyGetAccountInfoFromFile(char *username, char *filePath);
void zyRemoveAccountInfoFromFile(char *username, char *filePath);

#ifdef ABOG_CUSTOMIZATION
void zyTouchFile(int pid, char *ip);
void zyRemoveFile(int pid);
#endif

#ifdef ZYXEL_AT_SET_KEY
char *zyGetSupervisorPWD(void);
char *zyGetAdminPWD(void);
char *zyGetPSK(void);
#endif

/*!
 *  Check serial number format.
 *
 *  @param[in] char *str        Input string.
 *  @param[in] int len          Lenth of input string.
 *  @return                     0:ok; -1:error.
 */
int zyUtilChkSnFormat(char *str, int len);

/*!
 *  Check GPON serial number format.
 *
 *  @param[in] char *str        Input string.
 *  @param[in] int inputLen     Lenth of input string.
 *  @param[in] int chkLen       Lenth want to check.
 *  @return                     0:ok; -1:error.
 */
int zyUtilChkGPONSnFormat(char *str, int inputLen, int chkLen);

/*!
 *  Check password format.
 *
 *  @param[in] char *str        Input string.
 *  @param[in] int inputLen     Lenth of input string.
 *  @param[in] int chkLen       Lenth want to check.
 *  @return                     0:ok; -1:error.
 */
int zyUtilChkPwdFormat(char *str, int inputLen, int chkLen);

#endif

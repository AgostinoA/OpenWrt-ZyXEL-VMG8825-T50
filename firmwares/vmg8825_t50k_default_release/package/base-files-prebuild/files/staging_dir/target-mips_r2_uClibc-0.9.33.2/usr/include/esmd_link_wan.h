#ifndef _ESMD_LINK_WAN_H
#define _ESMD_LINK_WAN_H

bool isDslLineLinkUp();
zcfgRet_t initWanLinkInfo();
void esmdAtmLinkStatusChanged(objIndex_t *, bool);
void esmdPtmLinkStatusChanged(objIndex_t *, bool);
void updateWanLinkStatus(const char *, bool skipEthWanAutoHuntProcess);
void updateOpticalLinkStatus(char *buf);
#ifdef ZYXEL_SFP_LINKUP_DELAYTIMES
bool updateSfpWanLinkStatus(const char *);
#endif
void esmdResetWanLinkStatus(int);
void wanConnctionReadyHandle(char *, uint8_t clientEid, uint32_t clientPid);
void wanConnctionLostHandle(char *, uint8_t clientEid, uint32_t clientPid);
//INTERNET_LED_CONTROL
void wanInternetLEDUpdate(void);
int getIPv6DefaultGatwayStatus(char *);
int getIPv4DefaultGatwayStatus(char *);

bool isVcAutoHuntEnable(void);
bool isVlanAutoHuntEnable(void);

//bool isEthLinkUp;
#ifdef HAWAIIAN_TELCOM
#define MAX_CHECK_TIMES 10
#define MAX_CHECK_DELAY 2
bool isAtmLinkUp;
bool isPtmLinkUp;
int oldWanServiceID;
int checkInternetLinkUpNum;
bool wanUnderHunting;

bool disableDefaultGatewayWAN(char *linkType);
void activeDefaultWAN(void);
bool checkDefaultWANisUp(void);

#endif

#endif

#include "zcfg_common.h"
#include "esmd.h"
#ifdef BROADCOM_PLATFORM
#include "esmd_brcm_wrapper.h"
#endif

void processKernelMonitor(void);
zcfgRet_t esmd_init(void);
void zyEnableWifiLED();
int updateLanLinkStatus(char *msgData);
void updateWANEthIfaceObjStatus(objIndex_t *, void *);
void handleWANAutoDetectETHDown(void);
bool handleWANAutoDetectETH(void);
void updateETHWANStatus(char *msgData);
void handleXtmUpInit(wanLinkType currXtmType, wanLinkType prevXTMType);
void esmdSupportCAT3Cable(void);
void esmdLanPhyReset();
//INTERNET_LED_CONTROL
#if !defined(ZYXEL_ZYINETLED)
void esmdWanCtlInternetLED(internet_led_t type, internet_led_state_t state);
#endif

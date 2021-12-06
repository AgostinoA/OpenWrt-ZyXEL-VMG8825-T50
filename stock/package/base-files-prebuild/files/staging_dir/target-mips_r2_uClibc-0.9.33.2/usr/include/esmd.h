#ifndef _ESMD_H
#define _ESMD_H
#ifdef ISKON_CUSTOMIZATION_Motorola_VIP1003
#include <time.h>
#endif

int esmdApplyAddObjectTmTask(const char *, int , int , const char *);
int esmdApplyDeleteObjectTmTask(const char *);

void updateLinkStatus(const char*);
//void updateLanLinkStatus(void);
//void updateWanLinkStatus(void);
void emailEventHandle(char *buf, uint8_t clientEid, uint32_t clientPid);

#ifdef ZYXEL_SFP_LINKUP_DELAYTIMES
enum {
	sfpLinkUpPrepare = 0,
	sfpLinkupDelay,
	sfpLinkUpContinue
};
#endif

#ifdef ZYXEL_SIP_DELAYTIMES 
enum {
	SipPrepare = 0,
	SipDelayStatus,
	SipContinue
};
#endif

typedef enum {
		isATM,
		isPTM,
        isXTM,
        isEth,
        isMoca,
        isGpon,
        isEpon,
		isWwan,
		isMulti,
		none
} wanLinkType;


//INTERNET_LED_CONTROL
typedef enum{
	INTERNET_LED_FAIL = 0,
	INTERNET_LED_DATA
}internet_led_t;

typedef enum{
	INTERNET_LED_STATE_OFF = 0,
	INTERNET_LED_STATE_ON,
	INTERNET_LED_STATE_FAIL,
	INTERNET_LED_STATE_DONGLE,
	INTERNET_LED_STATE_NONE
}internet_led_state_t;

#ifdef ISKON_CUSTOMIZATION_Motorola_VIP1003
#define NUM_LAN_PORT 4
typedef struct {
	char portName[16];
	time_t time;
} sPortName;

extern sPortName lanPortName[NUM_LAN_PORT];
#endif
#endif

#define JSON_OBJ_COPY(json_object) json_tokener_parse(json_object_to_json_string(json_object))

#ifdef CONFIG_ZYXEL_HOME_CYBER_SECURITY_FSECURE
/* NTP update and notify F-secure */
extern void fsc_ntp_update ( void );
#endif

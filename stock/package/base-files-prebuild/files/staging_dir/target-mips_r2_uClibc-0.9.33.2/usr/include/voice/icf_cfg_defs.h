/*------------------------------------------------------------------------------
 *
 * File name        : icf_cfg_defs.h
 *
 * Purpose          : This file contains certain hash defines used by CFG.
 *
 * Revision History :
 *
 * Date         Name                Ref#        Comments
 * --------     ------------        ----        ---------------
 * 21-Jan-2005  Shefali Aggarwal    ICF LLD	Beginning of coding phase
 *
 * 27-Nov-2006  Deepti Goyal        ICF Rel6.2  NAT Feature Support
 *
 * Copyright (c) 2006, Aricent.
 *----------------------------------------------------------------------------*/


#ifndef __ICF_CFG_DEFS_H__
#define __ICF_CFG_DEFS_H__

#define ICF_CRM_START
#define ICF_CRM_END

/* Determine if a C++ compiler is being used.
 * If so, ensure that standard
 * C is used to process the API information.
 */

#ifdef __cplusplus

/* Yes, C++ compiler is present.
 * Use standard C.
 */

extern "C"
{
#endif /* __cplusplus */

/* default value of self port */
#define ICF_CFG_DEF_SELF_PORT            6060

/* default value of number of calls to log */
#define ICF_CFG_DEF_NUM_OF_CALLS_TO_LOG  0

#ifdef IMS_CLIENT   
/* default value of setup timer */
#define ICF_CFG_DEF_SETUP_TIMER          300000

/* default value of options timer */
#define ICF_CFG_DEF_OPTIONS_TIMER        120000

/* default value of alerting timer */
#define ICF_CFG_DEF_ALERTING_TIMER       140000

/* default value of release timer */
#define ICF_CFG_DEF_RELEASE_TIMER        240000
#else
/* default value of setup timer */
#define ICF_CFG_DEF_SETUP_TIMER          120000

/* default value of options timer */
#define ICF_CFG_DEF_OPTIONS_TIMER        30000

/* default value of alerting timer */
#define ICF_CFG_DEF_ALERTING_TIMER       35000

/* default value of release timer */
#define ICF_CFG_DEF_RELEASE_TIMER        60000
#endif
/* default value of modify media timer */
#define ICF_CFG_DEF_MODIFY_MEDIA_TIMER   5000

/* default value of INFO timer */
#define ICF_CFG_DEF_INFO_TIMER			 60000

#ifdef ICF_SESSION_TIMER
/*default value of session interval */
/*#define ICF_CFG_DEF_SESSION_TIMER_INTERVAL		3600*/
/* Changed the def value of session timer to 1800 as 
per requirement for per line feature Rel 6.3 */
#define ICF_CFG_DEF_SESSION_TIMER_INTERVAL	1800	
/*default value of minimum session interval*/
#define ICF_CFG_DEF_MIN_SESSION_TIMER_INTERVAL	90
#endif

ICF_CRM_START
/* Values of timer duration changed for ICF : RESP_TIMER made 35 sec
 * instead of 30 seconds: so that it expires after SSA timer which is 32 sec */

/* default value of registration response timer */

/*#define ICF_CFG_DEF_REG_RESP_TIMER       30000*/
#define ICF_CFG_DEF_REG_RESP_TIMER         35000

/* default value of registration retry timer */

/*#define ICF_CFG_DEF_REG_RETRY_TIMER      300000*/
/* ICF: RETRY_TIMER which is called the reattempt timer in REGM is made to
 * be of 1 second so that application receives REGISTER_CFM soon */
#define ICF_CFG_DEF_REG_RETRY_TIMER      1000

ICF_CRM_END

/* default value of registration response timer */
#define ICF_CFG_DEF_SUBS_RESP_TIMER       300000

/* default value of registration retry timer */
#define ICF_CFG_DEF_SUBS_RETRY_TIMER      300000

/* Number of services */
#define ICF_NUM_OF_SERVICES              10
    
/* default value of max number of call forwarding hops */
#define ICF_CFG_DEF_NUM_CALL_FWD_HOPS    2

/* default value of max number of calls in call waiting */
#define ICF_CFG_DEF_MAX_CALLS_WAITING    2

/* default value of CHR timer */
#define ICF_CFG_DEF_CHR_TIMER            60000

/* default value of Reinvite race timer */
#define ICF_CFG_DEF_REINVITE_RACE_TIMER  5000

/* default value of TWC timer */
#define ICF_CFG_DEF_TWC_TIMER            60000

/* default value of CTU timer */
#define ICF_CFG_DEF_CTU_TIMER            20000

/* default value of CTA timer */
#define ICF_CFG_DEF_CTA_TIMER            60000

/* default value of RNW timer */
#define ICF_CFG_DEF_RNW_TIMER            30000

/* default value of CW alerting timer */
#define ICF_CFG_DEF_CW_ALERT_TIMER       30000

/* default value of CND alerting timer */
#define ICF_CFG_DEF_CND_ALERT_TIMER      30000

/* default value of CW and CND alerting timer */
#define ICF_CFG_DEF_CW_N_CND_ALERT_TIMER 30000

/* default value of registration duration */
#define ICF_CFG_DEF_REG_DURATION_IMS_CLIENT         600000000
#define ICF_CFG_DEF_REG_DURATION_NON_IMS_CLIENT     3600000


/* default value of registration head start duration */
#define ICF_CFG_DEF_REG_HS_DURATION					0

/* default value of subscription head start duration */
#define ICF_CFG_DEF_SUBSCRIPTION_HS_DURATION		0

/* default value of sip timer T1 */
#define ICF_CFG_DEF_SIP_TIMER_T1					500

/* default value of sip timer T2 */
#define ICF_CFG_DEF_SIP_TIMER_T2					4000

/* default value of sip timer B */
#define ICF_CFG_DEF_SIP_TIMER_INVITE				32000

/* default value of sip timer F */
#define ICF_CFG_DEF_SIP_TIMER_NON_INVITE			32000

/* default value of sip timer T4 */
#define ICF_CFG_DEF_SIP_TIMER_T4    			    5000

/*Defines the default value of DNS minimum retransmission timer*/
#define ICF_CFG_DEF_DNS_MIN_RETRANS                            2000

/*defines the default value of DNS maximum retransmission timer*/
#define ICF_CFG_DEF_DNS_MAX_RETRANS                            32000

/* default value of SIP DSCP */
#define ICF_CFG_DEF_SIP_DSCP                        24

/* default value of RTP DSCP */
#define ICF_CFG_DEF_RTP_DSCP                        46

/* default value of session timer refresher */
#define ICF_CFG_DEF_SESSION_TIMER_REFRESHER         2


/* minimum number of lines allowed */
#define ICF_CFG_MIN_NUM_OF_LINES         1

/* minimum number of audio calls allowed */
#define ICF_CFG_MIN_AUDIO_CALLS          1

/* minimum number of service calls allowed */
#define ICF_CFG_MIN_SERVICE_CALLS        0

/* minimum number of users per line allowed */
#define ICF_CFG_MIN_USERS_PER_LINE       1

/* minimum number of registration calls allowed */
#define ICF_CFG_MIN_REGISTRATION_CALLS   0

/* minimum number of calls to log allowed */
#define ICF_CFG_MIN_NUM_CALLS_TO_LOG     0

/* minimum number of calls forwarding hops allowed */
#define ICF_CFG_MIN_NUM_CALL_FWD_HOPS    1

/* minimum number of calls in call waiting allowed */
#define ICF_CFG_MIN_NUM_CALLS_IN_WAITING 1

/* Denotes minimum permissible port number */
#define ICF_CFG_MIN_PORT_VALUE           1024

/* Denotes maximum permissible port number */
#define ICF_CFG_MAX_PORT_VALUE           65535

/* Denotes minimum value for a timer */
#define ICF_CFG_MIN_TIMER_VALUE          1

/* Parse states for filter expression string specified 
 * by the application in ADD_APP_REQ */
#define ICF_PARSE_STATE_PARSE_FAILED			0
#define ICF_PARSE_STATE_IN_STRING				1
#define ICF_PARSE_STATE_LOOKING_FOR_STRING		2
#define ICF_PARSE_STATE_LOOKING_FOR_OPERATOR	3

/* Default value of Binding Refresh timer
 */
#ifdef ICF_NAT_RPORT_SUPPORT
#define ICF_CFG_BINDING_REFRESH_TIMER   50000
#endif
#ifdef ICF_NAT_MEDIA_TRAVERSAL
#define ICF_CFG_NAT_STUN_MAX_CONTEXTS  70
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* End of __ICF_CFG_DEFS_H__ */


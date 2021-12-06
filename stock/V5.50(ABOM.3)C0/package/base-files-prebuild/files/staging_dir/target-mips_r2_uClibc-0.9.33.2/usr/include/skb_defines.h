#ifndef __SKB_DEFINEDS_H__
#define __SKB_DEFINEDS_H__

/* queue = mark[7:4] */
#define SKBMARK_Q_S             4
#define SKBMARK_Q_M             (0x0F << SKBMARK_Q_S)
#define SKBMARK_GET_Q(MARK)     ((MARK & SKBMARK_Q_M) >> SKBMARK_Q_S)
#define SKBMARK_SET_Q(MARK, Q)  ((MARK & ~SKBMARK_Q_M) | (Q << SKBMARK_Q_S))

/* guest_wlan_id = mark[27:27] */
#define SKBMARK_GWL_ID_S         27
#define SKBMARK_GWL_ID_M         (0x1 << SKBMARK_GWL_ID_S)
#define SKBMARK_GET_GWL_ID(MARK) \
	((MARK & SKBMARK_GWL_ID_M) >> SKBMARK_GWL_ID_S)
#define SKBMARK_SET_GWL_ID(MARK, TC) \
	((MARK & ~SKBMARK_GWL_ID_M) | (TC << SKBMARK_GWL_ID_S))
	
/* parental_control_id = mark[26:26] */
/* reuse for Voice port reserve */
#define SKBMARK_PC_ID_S         26
#define SKBMARK_PC_ID_M         (0x1 << SKBMARK_PC_ID_S)
#define SKBMARK_GET_PC_ID(MARK) ((MARK & SKBMARK_PC_ID_M) >> SKBMARK_PC_ID_S)
#define SKBMARK_SET_PC_ID(MARK, TC) \
    ((MARK & ~SKBMARK_PC_ID_M) | (TC << SKBMARK_PC_ID_S))	
	
/* flow_id = mark[15:12]; for QoS Classifier */
#define SKBMARK_FLOW_ID_S       12
#define SKBMARK_FLOW_ID_M       (0xF << SKBMARK_FLOW_ID_S)
#define SKBMARK_GET_FLOW_ID(MARK) \
    ((MARK & SKBMARK_FLOW_ID_M) >> SKBMARK_FLOW_ID_S)
#define SKBMARK_SET_FLOW_ID(MARK, FLOW) \
    ((MARK & ~SKBMARK_FLOW_ID_M) | (FLOW << SKBMARK_FLOW_ID_S))

/* VID_ACTION = mark[11:8], Change the bits used for Qos vlan operation. Original bits and WMM overlap */
#define SKBMARK_VID_ACTION_S       8
#define SKBMARK_VID_ACTION_M       (0xF << SKBMARK_VID_ACTION_S)
#define SKBMARK_GET_VID_ACTION(MARK) \
	((MARK & SKBMARK_VID_ACTION_M) >> SKBMARK_VID_ACTION_S)
#define SKBMARK_SET_VID_ACTION(MARK, FLOW) \
	((MARK & ~SKBMARK_VID_ACTION_M) | (FLOW << SKBMARK_VID_ACTION_S))

/* POLICER = mark[25:24], Change the bits used for Qos policer */
#define SKBMARK_POLICER_S       24
#define SKBMARK_POLICER_M       (0x03 << SKBMARK_POLICER_S)
#define SKBMARK_GET_POLICER(MARK) \
    ((MARK & SKBMARK_POLICER_M) >> SKBMARK_POLICER_S)
#define SKBMARK_SET_POLICER(MARK, FLOW) \
    ((MARK & ~SKBMARK_POLICER_M) | (FLOW << SKBMARK_POLICER_S))	

/* service route = mark[3:0]; for service route*/
#define SKBMARK_SERVICEROUTE_S          0
#define SKBMARK_SERVICEROUTE_M          (0x0f << SKBMARK_SERVICEROUTE_S)
#define SKBMARK_GET_SERVICEROUTE(MARK) \
	((MARK & SKBMARK_SERVICEROUTE_M) >> SKBMARK_SERVICEROUTE_S)
#define SKBMARK_SET_SERVICEROUTE(MARK, SERVICEROUTE) \
	((MARK & ~SKBMARK_SERVICEROUTE_M) | (SERVICEROUTE << SKBMARK_SERVICEROUTE_S))

/* iffwan_mark = mark[16]; check packet is form WAN interface */
#define SKBMARK_IFFWAN_MARK_S    16
#define SKBMARK_IFFWAN_MARK_M    (0x01 << SKBMARK_IFFWAN_MARK_S)
#define SKBMARK_GET_IFFWAN_MARK(MARK) \
    ((MARK & SKBMARK_IFFWAN_MARK_M) >> SKBMARK_IFFWAN_MARK_S)
#define SKBMARK_SET_IFFWAN_MARK(MARK, IFFWAN_MARK) \
    ((MARK & ~SKBMARK_IFFWAN_MARK_M) | (IFFWAN_MARK << SKBMARK_IFFWAN_MARK_S))

/* wlan_id = mark[17]; check packet is form wlan interface */
#define SKBMARK_WL_ID_S         17
#define SKBMARK_WL_ID_M         (0x01 << SKBMARK_WL_ID_S)
#define SKBMARK_GET_WL_ID(MARK) ((MARK & SKBMARK_WL_ID_M) >> SKBMARK_WL_ID_S)
#define SKBMARK_SET_WL_ID(MARK, WL_ID) \
	((MARK & ~SKBMARK_WL_ID_M) | (WL_ID << SKBMARK_WL_ID_S))
	
#endif
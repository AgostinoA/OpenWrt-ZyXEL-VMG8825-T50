#ifndef _EVENT_H
#define _EVENT_H

/*______________________________________________________________________________
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%	macro
%%____________________________________________________________________________*/
#define	EVENT( major, minor )		((major<<8) | minor)


#define EVENT_UPDATEINFORM 	0x30	/*update inform function*/	/* VOIP_NEW */
#define EVT_VOIP_PHONE		0x31	/* PHONE event for VoIP */	/* VOIP_NEW */
#define EVT_VOIP_CCM		0x32	/* CCM event for VoIP */	/* VOIP_NEW */
#define EVT_ISDN_CAPI		0x33	/* ISDN event for CAPI */
#ifdef NEW_ZYIMS_VOIP //Michael.20121023.001 *****************************************************************
#define EVT_TYPE_MASK		0xFF00
#define EVT_TYPE_SHIFT		8
#define EVT_ID_MASK			0x00FF
#endif //NEW_ZYIMS_VOIP //Michael.20121023.001 *****************************************************************

#endif /* _EVENT_H */




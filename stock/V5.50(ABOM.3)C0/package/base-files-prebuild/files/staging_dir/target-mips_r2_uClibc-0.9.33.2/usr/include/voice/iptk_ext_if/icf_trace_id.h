/*******************************************************************************
 *
 * FILENAME       : icf_trace_id.h
 *
 * DESCRIPTION    : This file contains the trace ids that shall be used within 
 *                  the IMS client framework.
 *                     
 * Revision History :
 * 
 * DATE         NAME                REFERENCE       REASON
 * -----------  -------------       ------------    --------------
 * 09-Aug-2004  Rohit Aggarwal                      Initial
 * 02-Feb-2006  Amit Sharma                         CFG merged with ICF 2.0
 * 10-Mar-2006  Amit Sharma                         ICF merging with ICF2.0
 * 16-Jan-2008   Amit Sharma       ICF 8.0 LLD      Enhancements for Rel8.0
 * 17-Jan-2008	Shruti Thakral						Enhancements for Rel 8.0 
 * 06-MAR-2008  Vipul Varshney      SPR 18122       AKA Enhancement 
 * 19-Mar-2008  Sumant Gupta       ICF 8.0          Merging of Publish & Message
 * 07-Jun-2008  Amit Sharma       IPTK 8.0 SRTP LLD SRTP Enhancements
 * 06-Feb-2009  Tarun Gupta       Rel 8.1 LLD       SDP Tunnelling Enhancements
 * 30-Mar-2009  Anurag Khare      Rel 8.2           Traces added for PRACK enh
 * 28-May-2009  Tarun Gupta       Rel 8.2           Async NOTIFY Support 
 * 31-May-2009  Preksha           Rel 8.2           Traces added for Asynchronus Message enh
 * Copyright (c) 2009, Aricent.
 ******************************************************************************/

#ifndef __ICF_TRACE_ID_H__
#define __ICF_TRACE_ID_H__

/* Determine if a C++ compiler is being used.
 * If so, ensure that standard
 * C is used to process the header information.
 * */

#ifdef __cplusplus

/* Yes, C++ compiler is present.
 * Use standard C.
 * */

extern "C"
{
#endif /* __cplusplus */


/******************** STANDARD INCLUDE FILES *****************************/

/******************** USER INCLUDE FILES *********************************/

/* -------------------------------------------------------------------------
 * Hash defined values of the trace ids for non-failure scenarios.
 * ------------------------------------------------------------------------*/

#define ICF_TRACE_UNDEFINED           0

/* min value of normal trace range */
#define ICF_TRACE_NORMAL_START        1

/* a module in software entered */
#define  ICF_TRACE_MODULE_ENTRY       1

/* module from software exit */
#define  ICF_TRACE_MODULE_EXIT        2

/* a function in software entered */
#define  ICF_TRACE_FUNCTION_ENTRY     3

/* a function from software exit */
#define  ICF_TRACE_FUNCTION_EXIT      4

/* setup received for a outgoing call from PA */
#define  ICF_TRACE_SETUP_RECVD_FRM_PA 5


/* -------------------------------------------------------------------------
 * Trace ids used by Call Control for non-failure scenarios.
 * ------------------------------------------------------------------------*/
/* Call Control FSM triggered */
#define ICF_TRACE_FSM_TRIGGERED       6
    
/* PA interface cleared */
#define ICF_TRACE_CALL_STATUS_PA_CLR  7

/* MM interface cleared */
#define ICF_TRACE_CALL_STATUS_MM_CLR  8

/* NW interface cleared */
#define ICF_TRACE_CALL_STATUS_NW_CLR  9

/* PA, NW and MM interfaces cleared */
#define ICF_TRACE_CALL_STATUS_ALL_CLR 10
    
/* call release process triggered by PA */
#define ICF_TRACE_REL_TYPE_PA_INIT    11

/* call release process triggered by MM */
#define ICF_TRACE_REL_TYPE_MM_INIT    12

/* call release process triggered by peer */
#define ICF_TRACE_REL_TYPE_NW_INIT    13

/* call release process triggered due to a timer expiry */
#define ICF_TRACE_REL_TYPE_TIMER_INIT 14

/* call release process triggered due to an internal error */
#define ICF_TRACE_REL_TYPE_INT_ERR    15

/* media state set to call mute */
#define ICF_TRACE_CALL_MUTE_SET       16

/* media state reset from call mute to unmute */
#define ICF_TRACE_CALL_MUTE_RESET     17

/* call direction - incoming or outgoing */
#define ICF_TRACE_CALL_DIR            18

/* incoming call setup type - FS or NFS */
#define ICF_TRACE_MEDIA_SETUP_TYPE    19

/* peer SDP received once and MMS request sent */
#define ICF_TRACE_MEDIA_COMMITTED     20

/* message received from peer contains SDP or not */
#define ICF_TRACE_SDP_IN_PEER_MSG     21

/* previous state in call context */
#define ICF_TRACE_PREVIOUS_STATE      22

/* previous state changed in call context */
#define ICF_TRACE_SET_PREVIOUS_STATE  23

/* current call state */
#define ICF_TRACE_CURRENT_STATE       24

/* current call state changed */
#define ICF_TRACE_SET_CURRENT_STATE   25

/* next state in call context */
#define ICF_TRACE_NEXT_STATE          26

/* next state changed in call context */
#define ICF_TRACE_SET_NEXT_STATE      27
    
/* current media mode applied to MM */
#define ICF_TRACE_MEDIA_MODE          28

/* media mode applied to MM changed */
#define ICF_TRACE_SET_MEDIA_MODE      29

/* media mode to be applied changed */
#define ICF_TRACE_SET_MODE_TO_BE_APP  30
    
/* call release cause set in call context */
#define ICF_TRACE_SET_RELEASE_CAUSE   31
    
/* media ongoing flag */
#define ICF_TRACE_MEDIA_ONGOING       32
 
/* media ongoing flag set */
#define ICF_TRACE_SET_MEDIA_ONGOING   33

/* signaling ongoing flag */
#define ICF_TRACE_SIG_ONGOING         34

/* signaling ongoing flag set */
#define ICF_TRACE_SET_SIG_ONGOING     35

/* ongoing event of Call Control */
#define ICF_TRACE_ONGOING_EVENT       36

/* ongoing event of Call Control set */
#define ICF_TRACE_SET_ONGOING_EVENT   37

/* inband info sent/received in a SIP message or not */
#define ICF_TRACE_INBAND_INFO         38

/* pending event is set or reset - User Answered */
#define ICF_TRACE_EVENT_PA_CONNECT    39

/* pending event is set or reset - PA Call terminate request */
#define ICF_TRACE_EVENT_PA_TERM_REQ   40

/* pending event is set or reset - MM Error indication */
#define ICF_TRACE_EVENT_MM_ERR_IND    41

/* pending event is set or reset - UPDATE/REINVITE from peer */
#define ICF_TRACE_EVENT_OFFER_CHANGE  42

/* pending event is set or reset - internal error */
#define ICF_TRACE_EVENT_INT_ERR       43

/* tells the timer that has expired */
#define ICF_TRACE_TIMER_EXPIRED       44

/* request sending to MMI succeeded or failed */
#define ICF_TRACE_SEND_MMI_REQ        45

/* payload of Delete Media Request */
#define ICF_TRACE_DMS_REQ_PAYLOAD     46
    
/* payload of Modify Media Request */
#define ICF_TRACE_MMS_REQ_PAYLOAD     47

/* whether provisional response is required for an outgoing NW message or not */
#define ICF_TRACE_PRACK_REQD          48

/* whether SDP needs to be sent in an outgoing NW message or not */
#define ICF_TRACE_MEDIA_TO_BE_SENT    49

/* pending event is set or reset - call mute */
#define ICF_TRACE_EVENT_CALL_MUTE     50

/* pending event is set or reset - call unmute */
#define ICF_TRACE_EVENT_CALL_UNMUTE   51
   
/* call failure because peer SDP was never received */
#define ICF_TRACE_CALL_FAIL_NO_SDP    52

/* timer started */
#define ICF_TRACE_START_TIMER         53

/* timer stopped */
#define ICF_TRACE_STOP_TIMER          54

/* Interface function returned failure */
#define ICF_INTERFACE_FAILURE         55

/* Sending ICF_PA_INCOMING_CALL_IND */
#define ICF_PA_INCOMING_CALL_IND      56

    /* Alert indication to/from  PA */
#define ICF_PA_ALERT_USER_IND         57    

 /*   ICF_PA_CONNECT_IND   */
#define ICF_PA_CONNECT_IND            58

 /*   CAll Terminated   */
#define ICF_PA_CALL_TERM_IND          59
    
 /*   CAll Terminate Resp to/from PA  */
#define ICF_PA_TERMINATE_CALL_RESP    60

 /*   CAll Terminate Resp to/from PA  */
#define ICF_PA_CALL_REDIRECTION_IND 61
    
 /*   CAll Terminate Resp to/from PA  */
#define ICF_PA_CALL_HOLD_IND          62
    
 /*   CAll Terminate Resp to/from PA  */
#define ICF_PA_CALL_RESUME_IND        63

   /*   media connect ind to PA  */
#define ICF_PA_MEDIA_CONNECT          64
 
    /*   Unexpected event received  */
#define ICF_UNEXPECTED_EVENT          65

    /*   Validation for diversion header failed  */
#define ICF_DIVERSION_INFO_VALIDATION_FAILED          66
    
    /* Trace to print ADDR in call ctx */ 
#define ICF_TRANSPORT_ADDRESS         67     
   
/* Status of Init Complete of CFG */
#define ICF_TRACE_INIT_COMPLETE_STATUS   68

/* flag indicating whether the received message contains valid param values */
#define ICF_TRACE_PARAM_VALIDITY      69

/* Trace id for service status return to cm by CC*/
#define ICF_TRACE_SRVC_TRIG_STAT_RET 70

    /*Trace id for call term when no ctx found*/
#define ICF_PA_CALL_TERM_IND_NO_CTX 71

    /* Trace id for mms request*/
 
#define  ICF_TRACE_MEDIA_MODIFY_SENT 72

#define	 ICF_TRACE_CMS_REQ_SENT		73

#define	 ICF_TRACE_CMS_RESP_RECVD		74

#define	ICF_TRACE_ITH_LEVEL_VALIDATION_FAILED	75

#define	ICF_TRACE_MMS_RESP_RECVD	76

#define	ICF_TRACE_APP_REJECTED_STREAMS	77

#define	ICF_TRACE_NO_ACTIVE_STREAMS_LEFT	78

#define	ICF_TRACE_OFFER_CHANGE_FAILURE	79

/* -------------------------------------------------------------------------
 * Trace ids used by Call Manager for non-failure scenarios.
 * ------------------------------------------------------------------------*/

/* Status of processing of signal handler message */
#define ICF_MSG_PROC_STATUS           ICF_TRACE_OFFER_CHANGE_FAILURE + 1

/* the received internal message */
#define ICF_MSG_PROC_RECV_INT_MSG     ICF_MSG_PROC_STATUS + 1

/* the action to be taken for the received internal msg */
#define ICF_MSG_PROC_ACTION_RESULT    ICF_MSG_PROC_STATUS + 2

/* field value and type used for message routing */
#define ICF_MSG_PROC_FIELD_DATA       ICF_MSG_PROC_STATUS + 3

/* value of a particular field type set */
#define ICF_MSG_PROC_FIELD_TYPE       ICF_MSG_PROC_STATUS + 4

/* presence field used to check a bit validity */
#define ICF_MSG_PROC_PRESENCE_FIELD   ICF_MSG_PROC_STATUS + 5

/* a particular value of a field alongwith the operator to match */
#define ICF_MSG_PROC_VALUE_ACTION     ICF_MSG_PROC_STATUS + 6

/* the action to be taken for a particular value of a field */
#define ICF_MSG_PROC_ACTION           ICF_MSG_PROC_STATUS + 7

    
/*------------------------------------------------------------------------------
 *
 * always assign ICF_TRACE_NORMAL_END, the last trace id value of this 
 * group. 
------------------------------------------------------------------------------*/
#define ICF_TRACE_NORMAL_END          ICF_MSG_PROC_ACTION



/* -------------------------------------------------------------------------
 * Hash defined values of the trace ids corresponding to error ids.
 * ------------------------------------------------------------------------*/

#define ICF_TRACE_ERROR_START         ICF_TRACE_NORMAL_END

/* memory allocation failure */
#define ICF_TRACE_MEM_ALLOC_FAILURE   ICF_ERROR_MEM_ALLOC_FAILURE        \
                                         + ICF_TRACE_ERROR_START

/* memory free failure */
#define ICF_TRACE_MEM_FREE_FAILURE    ICF_ERROR_MEM_FREE_FAILURE         \
                                         + ICF_TRACE_ERROR_START

/* timer start failure */
#define ICF_TRACE_TMR_START_FAILURE   ICF_ERROR_TMR_START_FAILURE        \
                                         + ICF_TRACE_ERROR_START

/* timer stop failure */
#define ICF_TRACE_TMR_STOP_FAILURE    ICF_ERROR_TMR_STOP_FAILURE         \
                                         + ICF_TRACE_ERROR_START

/* API with invalid id received */
#define ICF_TRACE_INVALID_API_ID      ICF_ERROR_INVALID_API_ID           \
                                         + ICF_TRACE_ERROR_START


/* always assign ICF_TRACE_ERROR_END, the last trace id value of this
   group.
*/
#define ICF_TRACE_ERROR_END            ICF_TRACE_INVALID_API_ID




/* -------------------------------------------------------------------------
 * Hash defined values of the trace ids for failure scenarios but other than
 * error ids.
 * ------------------------------------------------------------------------*/

#define  ICF_TRACE_ASSERT_FAILED       ICF_TRACE_ERROR_END + 1

/* -------------------------------------------------------------------------
 * Hash defined values of the trace ids for CHR service
 * ------------------------------------------------------------------------*/
#define ICF_TRACE_CALL_HOLD_RECVD      ICF_TRACE_ASSERT_FAILED + 1  
#define ICF_TRACE_CALL_HOLD_SUCC_RESP  ICF_TRACE_ASSERT_FAILED + 2
#define ICF_TRACE_CALL_RESUME_RECVD    ICF_TRACE_ASSERT_FAILED + 3
#define ICF_TRACE_MMS_SEND             ICF_TRACE_ASSERT_FAILED + 4
#define ICF_TRACE_HOLD_REQ_TO_NW       ICF_TRACE_ASSERT_FAILED + 5
#define ICF_TRACE_HLD_SUCC_FROM_NW     ICF_TRACE_ASSERT_FAILED + 6
#define ICF_TRACE_RSM_REQ_TO_NW        ICF_TRACE_ASSERT_FAILED + 7
#define ICF_TRACE_RSM_RESP_FROM_NW     ICF_TRACE_ASSERT_FAILED + 8
#define ICF_TRACE_HLD_FAIL_FROM_NW     ICF_TRACE_ASSERT_FAILED + 9
#define ICF_TRACE_REQ_CANCEL_SEND      ICF_TRACE_ASSERT_FAILED + 10
#define ICF_TRACE_CANCEL_RESP_RECV     ICF_TRACE_ASSERT_FAILED + 11
#define ICF_TRACE_MED_ERR_DMS_IND      ICF_TRACE_ASSERT_FAILED + 12
#define ICF_TRACE_MED_ERR_MMS_FAIL     ICF_TRACE_ASSERT_FAILED + 13
#define ICF_TRACE_CHR_TIMER_EXPD       ICF_TRACE_ASSERT_FAILED + 14
#define ICF_TRACE_RACE_TIMER_EXPD      ICF_TRACE_ASSERT_FAILED + 15
#define ICF_TRACE_ST_PROC_SIG_RCVD     ICF_TRACE_ASSERT_FAILED + 16
#define ICF_TRACE_ST_PROC_MED_RCVD     ICF_TRACE_ASSERT_FAILED + 17
#define ICF_TRACE_CALL_RELEASED        ICF_TRACE_ASSERT_FAILED + 18
#define ICF_TRACE_CALL_ALREADY_HOLD    ICF_TRACE_ASSERT_FAILED + 19
#define ICF_TRACE_SERVICE_TERM_NORMAL  ICF_TRACE_ASSERT_FAILED + 20
#define ICF_TRACE_SERVICE_TERM_ERROR   ICF_TRACE_ASSERT_FAILED + 21
#define ICF_TRACE_CALL_REMOTE_HOLD     ICF_TRACE_ASSERT_FAILED + 22
#define ICF_TRACE_SET_ST_PROC_SIG      ICF_TRACE_ASSERT_FAILED + 23    
#define ICF_TRACE_SSA_FAIL_RESP        ICF_TRACE_ASSERT_FAILED + 24
#define ICF_TRACE_SSA_SUCC_RESP        ICF_TRACE_ASSERT_FAILED + 25
#define ICF_TRACE_CHR_STATE            ICF_TRACE_ASSERT_FAILED + 26
#define ICF_TRACE_CHR_EVENT            ICF_TRACE_ASSERT_FAILED + 27
#define ICF_TRACE_ONGOING_ACT          ICF_TRACE_ASSERT_FAILED + 28
#define ICF_TRACE_PENDING_EVT          ICF_TRACE_ASSERT_FAILED + 29
#define ICF_TRACE_MMI_FAIL_RESP        ICF_TRACE_ASSERT_FAILED + 30
#define ICF_TRACE_MMI_SUCC_RESP        ICF_TRACE_ASSERT_FAILED + 31
#define ICF_TRACE_SET_ST_PROC_MED      ICF_TRACE_ASSERT_FAILED + 32
#define ICF_TRACE_MED_ONGOING          ICF_TRACE_ASSERT_FAILED + 33
#define ICF_TRACE_CALL_ALRADY_ACTIVE   ICF_TRACE_ASSERT_FAILED + 34
#define ICF_TRACE_MMS_SUCC_RESP        ICF_TRACE_ASSERT_FAILED + 35
#define ICF_TRACE_CURR_RET_STATUS      ICF_TRACE_ASSERT_FAILED + 36

/* -------------------------------------------------------------------------
 * Hash defined values of the trace ids for SCM
 * ------------------------------------------------------------------------*/
#define ICF_TRACE_GET_GLB_DATA_FAILED        ICF_TRACE_ASSERT_FAILED + 37  
#define ICF_TRACE_API_RECVD                  ICF_TRACE_ASSERT_FAILED + 38  
#define ICF_TRACE_SVC_CONT_RECVD             ICF_TRACE_ASSERT_FAILED + 39  
#define ICF_TRACE_SVC_END_RECVD              ICF_TRACE_ASSERT_FAILED + 40  
#define ICF_TRACE_SL_CTX_FREED               ICF_TRACE_ASSERT_FAILED + 41  
#define ICF_TRACE_CH_SUCCESS_STATUS          ICF_TRACE_ASSERT_FAILED + 42  
#define ICF_TRACE_CR_SUCCESS_STATUS          ICF_TRACE_ASSERT_FAILED + 43  
#define ICF_TRACE_CALL_RELEASE_FORWARDED     ICF_TRACE_ASSERT_FAILED + 44  
#define ICF_TRACE_SVC_ERR_IND_STATUS         ICF_TRACE_ASSERT_FAILED + 45  
#define ICF_TRACE_CH_REQ_STATUS              ICF_TRACE_ASSERT_FAILED + 46  
#define ICF_TRACE_CR_REQ_STATUS              ICF_TRACE_ASSERT_FAILED + 47  
#define ICF_TRACE_START_PROC_MEDIA_STATUS    ICF_TRACE_ASSERT_FAILED + 48  
#define ICF_TRACE_START_PROC_SIG_STATUS      ICF_TRACE_ASSERT_FAILED + 49  
#define ICF_TRACE_SIG_EVENTS_REQ_STATUS      ICF_TRACE_ASSERT_FAILED + 50  
#define ICF_TRACE_MEDIA_EVENTS_REQ_STATUS    ICF_TRACE_ASSERT_FAILED + 51  
#define ICF_TRACE_ALL_SVC_ENDED              ICF_TRACE_ASSERT_FAILED + 52  
#define ICF_TRACE_INV_API_RECVD              ICF_TRACE_ASSERT_FAILED + 53  
#define ICF_TRACE_SEND_FAILURE_TO_PA         ICF_TRACE_ASSERT_FAILED + 54  
#define ICF_TRACE_SEND_FAILURE_TO_SL         ICF_TRACE_ASSERT_FAILED + 55  
#define ICF_TRACE_FAILURE_RESP_SEND_FAIL     ICF_TRACE_ASSERT_FAILED + 56  
#define ICF_TRACE_GET_HANDLER_SL             ICF_TRACE_ASSERT_FAILED + 57  
#define ICF_TRACE_SVC_REQ_ONE_CALL           ICF_TRACE_ASSERT_FAILED + 58  
#define ICF_TRACE_SVC_REQ_TWO_CALLS          ICF_TRACE_ASSERT_FAILED + 59  
#define ICF_TRACE_RNW_INV_STATE              ICF_TRACE_ASSERT_FAILED + 60  
#define ICF_TRACE_SVC_REQ_VALID              ICF_TRACE_ASSERT_FAILED + 61  
#define ICF_TRACE_SVC_CTX_CREATE             ICF_TRACE_ASSERT_FAILED + 62  
#define ICF_TRACE_SL_CTX_CREATE              ICF_TRACE_ASSERT_FAILED + 63  
#define ICF_TRACE_SVC_REQ_INVALID            ICF_TRACE_ASSERT_FAILED + 64  
#define ICF_TRACE_MSG_ROUTING_FAILED         ICF_TRACE_ASSERT_FAILED + 65  
#define ICF_TRACE_MSG_ROUTING_PROGRESS       ICF_TRACE_ASSERT_FAILED + 66  
#define ICF_TRACE_CALL_ID_EXTRACTED          ICF_TRACE_ASSERT_FAILED + 67  
#define ICF_TRACE_GET_CALL_CTX               ICF_TRACE_ASSERT_FAILED + 68  

/* -------------------------------------------------------------------------
 * Hash defined values of the trace ids for REGM module
 * ------------------------------------------------------------------------*/
/* Init Complete API received from CFG Module */
#define ICF_TRACE_INIT_COMPLETE_RECVD        ICF_TRACE_ASSERT_FAILED + 69
/* Init Complete Successfully done by RGM */
#define ICF_TRACE_INIT_COMPLETE_SUCCESSFUL   ICF_TRACE_ASSERT_FAILED + 70
/* Received request for User Address Modification from CFG */
#define ICF_TRACE_MODIFY_USER_ADDRESS_RECVD  ICF_TRACE_ASSERT_FAILED + 71
/* Processing User Address Modification Block */
#define ICF_TRACE_PROCESS_MODIFY_USER_BLK    ICF_TRACE_ASSERT_FAILED + 72
/* Triggering Registration State Machine */
#define ICF_TRACE_REGISTRATION_FSM_TRIGGERED ICF_TRACE_ASSERT_FAILED + 73
/* Starting ROLLBACK Processing due to failure of Modify User Address */
#define ICF_TRACE_MODIFY_USER_ROLLBACK       ICF_TRACE_ASSERT_FAILED + 74
/* Received request for Registrar Address Addition/Deletion from CFG */
#define ICF_TRACE_MODIFY_REG_ADDRESS_RECVD   ICF_TRACE_ASSERT_FAILED + 75
/* Processing Registrar Address Addition/Deletion Block's Node */
#define ICF_TRACE_PROCESS_MODIFY_REG_BLK     ICF_TRACE_ASSERT_FAILED + 76
/* Starting ROLLBACK Processing due to failure of ADD/DEL REGISTRAR Address */
#define ICF_TRACE_MODIFY_REG_ROLLBACK        ICF_TRACE_ASSERT_FAILED + 77
/* Received request for Modification of Registration Duration from CFG */
#define ICF_TRACE_MODIFY_DURATION_RECVD      ICF_TRACE_ASSERT_FAILED + 78
/* Processing Registration Duration Modification Block's Node */
#define ICF_TRACE_PROCESS_MODIFY_DUR_BLK     ICF_TRACE_ASSERT_FAILED + 79
/* Starting ROLLBACK Processing due to failure of Registration Duration
 * Modification 
 */
#define ICF_TRACE_MODIFY_DUR_ROLLBACK        ICF_TRACE_ASSERT_FAILED + 80
/* Event Unexpected in Current State */
#define ICF_TRACE_INVALID_STATE_EVENT        ICF_TRACE_ASSERT_FAILED + 81
/* Registration Retry Timer Expired */
#define ICF_TRACE_RETRY_TIMER_EXPIRY         ICF_TRACE_ASSERT_FAILED + 82
/* Registration Duration Expired */
#define ICF_TRACE_REG_TIMER_EXPIRY           ICF_TRACE_ASSERT_FAILED + 83
/* Registration Reattempt Timer Expired */
#define ICF_TRACE_REG_REATT_TIMER_EXPIRY     ICF_TRACE_ASSERT_FAILED + 84
/* Sending Registration Request */
#define ICF_TRACE_SENDING_REG_REQUEST        ICF_TRACE_ASSERT_FAILED + 85
/* Sending Deregistration Request */
#define ICF_TRACE_SENDING_DEREG_REQUEST      ICF_TRACE_ASSERT_FAILED + 86

/*Call context block allocated*/
#define ICF_CALL_CTX_ALLOCATE                ICF_TRACE_ASSERT_FAILED + 87

/*Service context block allocated*/
#define ICF_SRVC_CTX_ALLOCATE                ICF_TRACE_ASSERT_FAILED + 88  

/*Requested call context was found*/
#define ICF_CALL_CTX_FOUND                   ICF_TRACE_ASSERT_FAILED + 89

/*Requested service context was found*/    
#define ICF_SRVC_CTX_FOUND                   ICF_TRACE_ASSERT_FAILED + 90   

/*Call context block freed*/
#define ICF_CALL_CTX_FREED				     ICF_TRACE_ASSERT_FAILED + 91

#define ICF_DBM_BLOCK_ALLOCATED				 ICF_TRACE_ASSERT_FAILED + 92	

#define ICF_DBM_BLOCK_DEALLOCATED			 ICF_TRACE_ASSERT_FAILED + 93

#define ICF_TRACE_XCONF_NEW_CALL_ID          ICF_TRACE_ASSERT_FAILED + 94

#define ICF_TRACE_XCONF_STATE                ICF_TRACE_ASSERT_FAILED + 95

#define ICF_TRACE_XCONF_EVENT                ICF_TRACE_ASSERT_FAILED + 96

/*---------------------------------------------------------------------------
 * 
 * Hash defines for MMI
 * ------------------------------------------------------------------------*/
#define ICF_TRACE_MMI_START              ICF_DBM_BLOCK_DEALLOCATED
#define ICF_EVENT_RECVD                  ICF_TRACE_MMI_START + 1
#define ICF_TRACE_API_SEND               ICF_TRACE_MMI_START + 2
#define ICF_TRACE_MMS_FOR_CODEC_CHANGE   ICF_TRACE_MMI_START + 3
#define ICF_TRACE_MEDIA_COMMITED         ICF_TRACE_MMI_START + 4
#define ICF_TRACE_MEDIA_NOT_COMMITED     ICF_TRACE_MMI_START + 5
#define ICF_TRACE_DMS_NOT_FORCEFUL       ICF_TRACE_MMI_START + 6
#define ICF_TRACE_FORCEFUL_DMS           ICF_TRACE_MMI_START + 7
#define ICF_TRACE_FAILURE_RESP           ICF_TRACE_MMI_START + 8
#define ICF_TRACE_SUCCESS_RESP           ICF_TRACE_MMI_START + 9
#define ICF_TRACE_CC_AWT_DMS             ICF_TRACE_MMI_START + 10
#define ICF_TRACE_MEDIA_ESTABLISHED      ICF_TRACE_MMI_START + 11
#define ICF_TRACE_MEDIA_NOT_ESTABLISHED  ICF_TRACE_MMI_START + 12
#define ICF_TRACE_MODIFY_FOR_CODEC_CHANGE_SET ICF_TRACE_MMI_START + 13
#define ICF_TRACE_RESTORATION_IN_PROGRESS_SET ICF_TRACE_MMI_START + 14
#define ICF_TRACE_MMS_FOR_MODE_CHANGE    ICF_TRACE_MMI_START + 15
#define ICF_TRACE_MMS_WITH_REMOTE_SDP    ICF_TRACE_MMI_START + 16
#define ICF_TRACE_MODIFY_FOR_REMOTE_MEDIA_APPLICATION_SET \
                                            ICF_TRACE_MMI_START + 17 
#define ICF_TRACE_CALL_INCOMING_FS       ICF_TRACE_MMI_START + 18
#define ICF_TRACE_FAILURE_TO_SEND        ICF_TRACE_MMI_START + 19
#define ICF_TRACE_FAILURE_BY_CM          ICF_TRACE_MMI_START + 20
#define ICF_TRACE_FAILURE_TO_PROCESS_MSG ICF_TRACE_MMI_START + 21
#define ICF_TRACE_FAILURE_BY_DBM         ICF_TRACE_MMI_START + 22
#define ICF_TRACE_UNEXPECTED_EVENT       ICF_TRACE_MMI_START + 23
#define ICF_MMI_TRACE_CURRENT_STATE      ICF_TRACE_MMI_START + 24
#define ICF_TRACE_MMS_FOR_REMOTE_MEDIA_CHANGE \
                                            ICF_TRACE_MMI_START + 25
#define ICF_TRACE_MMS_FOR_REMOTE_MEDIA_APPLICATION \
                                            ICF_TRACE_MMI_START + 26 
#define ICF_TRACE_NUM_OF_LOCAL_CODECS \
                                            ICF_TRACE_MMI_START + 27 
#define ICF_TRACE_NEGOTIATION_FAILURE    ICF_TRACE_MMI_START + 28
#define ICF_TRACE_HDR_SEND               ICF_TRACE_MMI_START + 29
#define ICF_TRACE_GCL_DATA_SEND          ICF_TRACE_MMI_START + 30
#define ICF_TRACE_NUM_OF_CODECS          ICF_TRACE_MMI_START + 31    
#define ICF_TRACE_CODEC                  ICF_TRACE_MMI_START + 32
#define ICF_TRACE_MMS_DATA_SEND          ICF_TRACE_MMI_START + 33
#define ICF_TRACE_MMS_SDP_SEND           ICF_TRACE_MMI_START + 34   
#define ICF_TRACE_MMS_ADDR_SEND          ICF_TRACE_MMI_START + 35
#define ICF_TRACE_COMMIT_DATA_SEND       ICF_TRACE_MMI_START + 36         
#define ICF_TRACE_CALL_OTG_OR_INC_NFS \
                                            ICF_TRACE_MMI_START + 37
#define ICF_TRACE_CMS_DATA_SEND          ICF_TRACE_MMI_START + 38
#define ICF_TRACE_LOCAL_AUDIO_CODEC_LIST ICF_TRACE_MMI_START + 39    
#define ICF_TRACE_REMOTE_SDP             ICF_TRACE_MMI_START + 40
#define ICF_TRACE_CMS_SDP_SEND           ICF_TRACE_MMI_START + 41
#define ICF_TRACE_CMS_ADDR_SEND          ICF_TRACE_MMI_START + 42    
#define ICF_TRACE_GCL_DATA_RECVD         ICF_TRACE_MMI_START + 43
#define ICF_TRACE_CMS_DATA_RECVD	        ICF_TRACE_MMI_START + 44
#define ICF_TRACE_CMS_SDP_RECVD	        ICF_TRACE_MMI_START + 45
#define ICF_TRACE_ADDR			         ICF_TRACE_MMI_START + 46
#define ICF_TRACE_MERGE_DATA_SEND	    ICF_TRACE_MMI_START + 47
#define ICF_TRACE_MED_CAP_REQ           ICF_TRACE_MMI_START + 48
#define ICF_TRACE_MED_CAP_RESP          ICF_TRACE_MMI_START + 49
#define ICF_TRACE_OCR_DATA_RECVD		ICF_TRACE_MMI_START + 50
#define ICF_TRACE_MMS_DATA_RECVD        ICF_TRACE_MMI_START + 51

#define ICF_TRACE_OPEN_CHANNEL_DATA_SEND	ICF_TRACE_MMI_START + 52
#define ICF_TRACE_CLOSE_CHANNEL_DATA_SEND	ICF_TRACE_MMI_START + 53
#define	ICF_TRACE_REL_RES_DATA_SEND		ICF_TRACE_MMI_START + 54
#define ICF_TRACE_DMS_DATA_SEND			ICF_TRACE_MMI_START + 55
#define ICF_TRACE_STREAM_ID				ICF_TRACE_MMI_START + 56
#define ICF_TRACE_STREAM_TYPE			ICF_TRACE_MMI_START + 57

#define ICF_TRACE_MMI_END				ICF_TRACE_STREAM_TYPE + 1

/******************************************************************************
 * Some more CHR traces
 ****************************************************************************/
#define ICF_TRACE_CHR_START                 ICF_TRACE_MMI_END
#define ICF_TRACE_NO_SDP_PRESENT            ICF_TRACE_CHR_START + 1
#define ICF_TRACE_NUMBER_OF_CODEC_DIFF      ICF_TRACE_CHR_START + 2
#define ICF_TRACE_CODEC_DIFF                ICF_TRACE_CHR_START + 3
#define ICF_TRACE_CODEC_SAME                ICF_TRACE_CHR_START + 4
#define ICF_TRACE_TRANSPORT_ADDR_DIFF       ICF_TRACE_CHR_START + 5
#define ICF_TRACE_PACKETIZATION_DIFF        ICF_TRACE_CHR_START + 6
#define ICF_TRACE_SDP_SAME                  ICF_TRACE_CHR_START + 7

/* -------------------------------------------------------------------------
 * Hash defined values of the trace ids for TWC service
 * ------------------------------------------------------------------------*/

#define  ICF_TRACE_TWC_START                ICF_TRACE_SDP_SAME
#define  ICF_TRACE_TWC_RECVD                ICF_TRACE_TWC_START + 1
#define  ICF_TRACE_MERGE_MEDIA_RESP         ICF_TRACE_TWC_START + 2
#define  ICF_TRACE_BOTH_CALL_ACTIVE         ICF_TRACE_TWC_START + 3
#define  ICF_TRACE_TWC_STATE                ICF_TRACE_TWC_START + 4
#define  ICF_TRACE_TWC_EVENT                ICF_TRACE_TWC_START + 5
#define  ICF_TWC_TRACE_MEDIA_NOT_COMMITTED  ICF_TRACE_TWC_START + 6
#define  ICF_TWC_TRACE_CALL_LOCAL_HOLD      ICF_TRACE_TWC_START + 7
#define  ICF_TWC_TRACE_END_OTHER_CALL       ICF_TRACE_TWC_START + 8
#define  ICF_TWC_TRACE_TERMINATE_SERVICE    ICF_TRACE_TWC_START + 9
#define  ICF_TWC_TRACE_MEDIA_ONGOING        ICF_TRACE_TWC_START + 10
#define  ICF_TWC_TRACE_MERGE_MEDIA_SENT     ICF_TRACE_TWC_START + 11
#define  ICF_TWC_TRACE_FAILURE_CONF_RESP_SENT   ICF_TRACE_TWC_START + 12
#define  ICF_TWC_TRACE_BOTH_CALLS_ENDED         ICF_TRACE_TWC_START + 13
#define  ICF_TWC_TRACE_CHR_SERVICE_ACTIVE_CHD   ICF_TRACE_TWC_START + 14
#define  ICF_TWC_TRACE_CHR_SERVICE_ACTIVE_CRM   ICF_TRACE_TWC_START + 15
#define  ICF_TWC_TRACE_INVALID_SERVICE_SCENARIO ICF_TRACE_TWC_START + 16
#define  ICF_TWC_TRACE_BOTH_CALL_ENDED          ICF_TRACE_TWC_START + 17

/* -------------------------------------------------------------------------
 * Hash defined values of the trace ids for CTU service
 * ------------------------------------------------------------------------*/

#define  ICF_TRACE_CTU_RECVD           ICF_TWC_TRACE_BOTH_CALL_ENDED + 1

#define  ICF_CTU_TRACE_CALL_RESUME_RESP_RECVD  \
                           ICF_TWC_TRACE_BOTH_CALL_ENDED + 2

#define  ICF_CTU_TRACE_CALL_HOLD_RESP_RECVD  \
                           ICF_TWC_TRACE_BOTH_CALL_ENDED + 3

#define  ICF_CTU_TRACE_REFER_REQ_SENT  ICF_TWC_TRACE_BOTH_CALL_ENDED + 4

#define  ICF_CTU_TRACE_REFER_REQ_WITH_REF_BY  \
                           ICF_TWC_TRACE_BOTH_CALL_ENDED + 5

#define  ICF_CTU_TRACE_PA_INITIATED_CALL_REL \
                           ICF_TWC_TRACE_BOTH_CALL_ENDED + 6

#define  ICF_CTU_TRACE_CC_INITIATED_CALL_REL  \
                           ICF_TWC_TRACE_BOTH_CALL_ENDED + 7

#define  ICF_CTU_TRACE_INVALID_ADDRESS   \
                           ICF_TWC_TRACE_BOTH_CALL_ENDED + 8

#define  ICF_TRACE_TEL_URL             ICF_TWC_TRACE_BOTH_CALL_ENDED + 9
#define  ICF_TRACE_INVALID_TEL_URL     ICF_TWC_TRACE_BOTH_CALL_ENDED + 10
#define  ICF_TRACE_E164_URL            ICF_TWC_TRACE_BOTH_CALL_ENDED + 11
#define  ICF_TRACE_INVALID_E164_URL    ICF_TWC_TRACE_BOTH_CALL_ENDED + 12
#define  ICF_TRACE_SIP_URL             ICF_TWC_TRACE_BOTH_CALL_ENDED + 13
#define  ICF_TRACE_INVALID_SIP_URL     ICF_TWC_TRACE_BOTH_CALL_ENDED + 14
#define  ICF_TRACE_CTU_STATE     ICF_TWC_TRACE_BOTH_CALL_ENDED + 15

#define  ICF_TRACE_CTU_EVENT     ICF_TWC_TRACE_BOTH_CALL_ENDED + 16
                                         

/*----------------------------------------------------------------------------
 *                            Traces for CFG
 *---------------------------------------------------------------------------*/
#define ICF_CFG_TRACE_SCALABLE_LINE_PRMS_REQ_RECD \
                           ICF_TRACE_CTU_EVENT + 1

#define ICF_CFG_TRACE_SCALABLE_CALL_PRMS_REQ_RECD \
                           ICF_TRACE_CTU_EVENT + 2

#define ICF_CFG_TRACE_TRNSPT_PRMS_REQ_RECD      ICF_TRACE_CTU_EVENT + 3

#define ICF_CFG_TRACE_PROXY_ADDR_REQ_RECD       ICF_TRACE_CTU_EVENT + 4
                           
#define ICF_CFG_TRACE_PROXY_ADDR_LINE_RECD      ICF_TRACE_CTU_EVENT + 5

#define ICF_CFG_TRACE_PROXY_ADDR_RECD           ICF_TRACE_CTU_EVENT + 6
                           
#define ICF_CFG_TRACE_SELF_TRNSPT_ADDR_RECD     ICF_TRACE_CTU_EVENT + 7

#define ICF_CFG_TRACE_CALL_PARAMS_RECD          ICF_TRACE_CTU_EVENT + 8
                           
#define ICF_CFG_TRACE_CALL_DEFAULT_SETTING_N_QOS_RECD \
                           ICF_TRACE_CTU_EVENT + 9

#define ICF_CFG_TRACE_CALL_TIMERS_RECD          ICF_TRACE_CTU_EVENT + 10

#define ICF_CFG_TRACE_REG_TIMERS_RECD           ICF_TRACE_CTU_EVENT + 11

#define ICF_CFG_TRACE_SELF_ID_PRMS_REQ_RECD     ICF_TRACE_CTU_EVENT + 12

#define ICF_CFG_TRACE_SELF_ID_ADDR_PRMS_RECD    ICF_TRACE_CTU_EVENT + 13

#define ICF_CFG_TRACE_SELF_ID_NAME_PRMS_RECD    ICF_TRACE_CTU_EVENT + 14
                           
#define ICF_CFG_TRACE_SELF_ID_DEF_PRMS_RECD     ICF_TRACE_CTU_EVENT + 15

#define ICF_CFG_TRACE_SELF_ADDR_RECD            ICF_TRACE_CTU_EVENT + 16
                           
#define ICF_CFG_TRACE_SELF_NAME_RECD            ICF_TRACE_CTU_EVENT + 17

#define ICF_CFG_TRACE_SELF_DEF_RECD             ICF_TRACE_CTU_EVENT + 18

#define ICF_CFG_TRACE_REG_PRMS_REQ_RECD         ICF_TRACE_CTU_EVENT + 19
                           
#define ICF_CFG_TRACE_REG_ADDR_PRMS_RECD        ICF_TRACE_CTU_EVENT + 20

#define ICF_CFG_TRACE_REG_ADDR_RECD             ICF_TRACE_CTU_EVENT + 21

#define ICF_CFG_TRACE_REG_PRMS_RECD             ICF_TRACE_CTU_EVENT + 22

#define ICF_CFG_TRACE_SRVC_PRMS_REQ_RECD        ICF_TRACE_CTU_EVENT + 23
                           
#define ICF_CFG_TRACE_SRVC_TIMERS_RECD          ICF_TRACE_CTU_EVENT + 24

#define ICF_CFG_TRACE_CALL_FWD_TIMERS_RECD      ICF_TRACE_CTU_EVENT + 25

#define ICF_CFG_TRACE_SRVC_FLAGS_PRMS_RECD      ICF_TRACE_CTU_EVENT + 26

#define ICF_CFG_TRACE_SRVC_FLAGS_RECD           ICF_TRACE_CTU_EVENT + 27

#define ICF_CFG_TRACE_CFU_ADDR_PRMS_RECD        ICF_TRACE_CTU_EVENT + 28

#define ICF_CFG_TRACE_CFU_ADDR_RECD             ICF_TRACE_CTU_EVENT + 29

#define ICF_CFG_TRACE_CFB_ADDR_PRMS_RECD        ICF_TRACE_CTU_EVENT + 30

#define ICF_CFG_TRACE_CFB_ADDR_RECD             ICF_TRACE_CTU_EVENT + 31

#define ICF_CFG_TRACE_CFD_ADDR_PRMS_RECD        ICF_TRACE_CTU_EVENT + 32

#define ICF_CFG_TRACE_CFD_ADDR_RECD             ICF_TRACE_CTU_EVENT + 33
                           
#define ICF_CFG_TRACE_RESP_SENT                 ICF_TRACE_CTU_EVENT + 34

#define ICF_CFG_TRACE_SCALABLE_LINE_PRMS_SET    ICF_TRACE_CTU_EVENT + 35

#define ICF_CFG_TRACE_SCALABLE_CALL_PRMS_SET    ICF_TRACE_CTU_EVENT + 36

#define ICF_CFG_TRACE_PROXY_ADDR_LINE_SET       ICF_TRACE_CTU_EVENT + 37 

#define ICF_CFG_TRACE_PROXY_ADDRESS_SET         ICF_TRACE_CTU_EVENT + 38

#define ICF_CFG_TRACE_SELF_TRNSPT_ADDR_SET      ICF_TRACE_CTU_EVENT + 39

#define ICF_CFG_TRACE_SELF_TRNSPT_MODE_SET      ICF_TRACE_CTU_EVENT + 40

/*#define ICF_CFG_TRACE_NUM_OF_CALLS_TO_LOG_SET   ICF_TRACE_CTU_EVENT + 41*/

#define ICF_CFG_TRACE_CALL_DEFAULT_SETTING_N_QOS_SET \
                           ICF_TRACE_CTU_EVENT + 42

#define ICF_CFG_TRACE_CALL_TIMERS_SET           ICF_TRACE_CTU_EVENT + 43

#define ICF_CFG_TRACE_REG_TIMERS_SET            ICF_TRACE_CTU_EVENT + 44

#define ICF_CFG_TRACE_MAX_NUM_OF_USERS_REACHED \
                           ICF_TRACE_CTU_EVENT + 45

#define ICF_CFG_TRACE_SELF_ADDR_SET             ICF_TRACE_CTU_EVENT + 46
                           
#define ICF_CFG_TRACE_SELF_NAME_SET             ICF_TRACE_CTU_EVENT + 47

#define ICF_CFG_TRACE_SELF_DEFAULT_SETTINGS_SET \
                           ICF_TRACE_CTU_EVENT + 48

#define ICF_CFG_TRACE_LINE_BLK_DEALLOCATED      ICF_TRACE_CTU_EVENT + 49

#define ICF_CFG_TRACE_REQ_ALREADY_RECD          ICF_TRACE_CTU_EVENT + 50
                           
#define ICF_CFG_TRACE_REG_ADDR_SET              ICF_TRACE_CTU_EVENT + 51

#define ICF_CFG_TRACE_REG_PRMS_SET              ICF_TRACE_CTU_EVENT + 52

#define ICF_CFG_TRACE_SRVC_PRMS_SET             ICF_TRACE_CTU_EVENT + 53

#define ICF_CFG_TRACE_SRVC_TIMERS_SET           ICF_TRACE_CTU_EVENT + 54

#define ICF_CFG_TRACE_CALL_FWD_TIMERS_SET       ICF_TRACE_CTU_EVENT + 55

#define ICF_CFG_TRACE_SRVC_FLAGS_SET            ICF_TRACE_CTU_EVENT + 56

#define ICF_CFG_TRACE_CFU_ADDR_SET              ICF_TRACE_CTU_EVENT + 57

#define ICF_CFG_TRACE_CFB_ADDR_SET              ICF_TRACE_CTU_EVENT + 58

#define ICF_CFG_TRACE_CFD_ADDR_SET              ICF_TRACE_CTU_EVENT + 59

#define ICF_CFG_TRACE_CALL_PRMS_SET          ICF_TRACE_CTU_EVENT + 60

#define ICF_CFG_TRACE_SELF_ADDR_PRMS_SET     ICF_TRACE_CTU_EVENT + 61

#define ICF_CFG_TRACE_SELF_NAME_N_DEF_SET_RECD ICF_TRACE_CTU_EVENT + 62

#define ICF_CFG_TRACE_SRVC_SUBSCRIBE_PRMS_SET	ICF_TRACE_CTU_EVENT + 63

#define ICF_CFG_TRACE_CFU_ADDR_PRMS_SET			ICF_TRACE_CTU_EVENT + 64

#define ICF_CFG_TRACE_CFB_ADDR_PRMS_SET			ICF_TRACE_CTU_EVENT + 65

#define ICF_CFG_TRACE_CFD_ADDR_PRMS_SET			ICF_TRACE_CTU_EVENT + 66

#define ICF_CFG_TRACE_SRVC_SUBS_FLAG_RECD		ICF_TRACE_CTU_EVENT + 67

#define ICF_CFG_TRACE_SRVC_ACT_FLAG_RECD		ICF_TRACE_CTU_EVENT + 68
#define ICF_CFG_TRACE_SRVC_SUBSCRIBE_PRMS_RECD	ICF_TRACE_CTU_EVENT + 69
#define ICF_CFG_TRACE_VMS_PRMS_RECD             ICF_TRACE_CTU_EVENT + 70
#define ICF_CFG_TRACE_VMS_ADDR_PRMS_RECD        ICF_TRACE_CTU_EVENT + 71
#define ICF_CFG_TRACE_VMS_OTHER_PRMS_RECD       ICF_TRACE_CTU_EVENT + 72
#define ICF_CFG_TRACE_SEC_PROXY_ADDR_REQ_RECD   ICF_TRACE_CTU_EVENT + 73
#define ICF_CFG_TRACE_SEC_PROXY_ADDR_RECD		ICF_TRACE_CTU_EVENT + 74
#define ICF_CFG_TRACE_SEC_PROXY_ADDRESS_SET     ICF_TRACE_CTU_EVENT + 75
#define ICF_CFG_TRACE_DNS_SERVER_ADDR_RECD      ICF_TRACE_CTU_EVENT + 76
#define ICF_CFG_TRACE_SEC_DNS_SERVER_ADDR_RECD	ICF_TRACE_CTU_EVENT + 77
#define ICF_CFG_TRACE_SEC_REG_ADDR_RECD         ICF_TRACE_CTU_EVENT + 78
#define ICF_CFG_TRACE_SEC_REG_ADDR_SET			ICF_TRACE_CTU_EVENT + 79
#define ICF_CFG_TRACE_SEC_REG_PRMS_RECD         ICF_TRACE_CTU_EVENT + 80
#define ICF_CFG_TRACE_SEC_REG_PRMS_REQ_RECD     ICF_TRACE_CTU_EVENT + 81

/* -------------------------------------------------------------------------
 * Some More trace ids for REGM Module
 * ------------------------------------------------------------------------*/
#define ICF_TRACE_DEREG_SUCCESS_RESP      ICF_CFG_TRACE_SEC_REG_PRMS_REQ_RECD + 1
#define ICF_TRACE_REG_SUCCESS_RESP        ICF_CFG_TRACE_SRVC_SUBSCRIBE_PRMS_RECD + 2
#define ICF_TRACE_DEREG_FAIL_RESP         ICF_CFG_TRACE_SRVC_SUBSCRIBE_PRMS_RECD + 3
#define ICF_TRACE_REG_FAIL_RESP           ICF_CFG_TRACE_SRVC_SUBSCRIBE_PRMS_RECD + 4
#define ICF_TRACE_DEREG_FAIL_NO_REATT_RESP ICF_CFG_TRACE_SRVC_SUBSCRIBE_PRMS_RECD + 5
#define ICF_TRACE_REG_FAIL_NO_REATT_RESP  ICF_CFG_TRACE_SRVC_SUBSCRIBE_PRMS_RECD + 6
#define ICF_TRACE_AUTHENTICATION_REQ      ICF_CFG_TRACE_SRVC_SUBSCRIBE_PRMS_RECD + 7
#define ICF_TRACE_DURATION_SHORT          ICF_CFG_TRACE_SRVC_SUBSCRIBE_PRMS_RECD + 8

/*------------------------------------------------------------------
 * API related Traces for SM Handler. 
 * ----------------------------------------------------------------*/
#define ICF_SM_TRACE_START                ICF_TRACE_DURATION_SHORT
#define ICF_SM_TRACE_TRACE_LVL_REQ_RECD   ICF_SM_TRACE_START + 1
#define ICF_SM_TRACE_ERROR_LVL_REQ_RECD   ICF_SM_TRACE_START + 2 
#define ICF_SM_TRACE_SET_STATS_REQ_RECD   ICF_SM_TRACE_START + 3
#define ICF_SM_TRACE_GET_STATS_REQ_RECD   ICF_SM_TRACE_START + 4
#define ICF_SM_TRACE_GET_STATS_RESP_SENT  ICF_SM_TRACE_START + 5
#define ICF_SM_TRACE_CHK_MODULE_REQ_RECD  ICF_SM_TRACE_START + 6
#define ICF_SM_TRACE_CHK_MODULE_RESP_SENT ICF_SM_TRACE_START + 7
#define ICF_SM_TRACE_CALL_LOG_REQ_RECD    ICF_SM_TRACE_START + 8
#define ICF_SM_TRACE_CALL_LOG_RESP_SENT   ICF_SM_TRACE_START + 9
#define ICF_SM_TRACE_VALIDATE_PARAM       ICF_SM_TRACE_START + 10

/*----------------------------------------------------------------
 * Non API traces for SM Handler
 * ------------------------------------------------------------- */
#define ICF_SM_TRACE_NUM_CALLS_RECORD     ICF_SM_TRACE_START + 11
#define ICF_SM_TRACE_DIALED_CALL_LOG_REQ  ICF_SM_TRACE_START + 12
#define ICF_SM_TRACE_DIALED_CALL_LOG_RESP ICF_SM_TRACE_START + 13
#define ICF_SM_TRACE_MISSED_CALL_LOG_REQ  ICF_SM_TRACE_START + 14
#define ICF_SM_TRACE_MISSED_CALL_LOG_RESP ICF_SM_TRACE_START + 15
#define ICF_SM_TRACE_RECD_CALL_LOG_REQ    ICF_SM_TRACE_START + 16
#define ICF_SM_TRACE_RECD_CALL_LOG_RESP   ICF_SM_TRACE_START + 17
   
/*---------------------------------------------------------------------
 * Some more trace ids for CFG Module
 * -------------------------------------------------------------------*/
#define ICF_TRACE_INVALID_MSG_ID_RECD      ICF_TRACE_CTU_EVENT + 89
#define ICF_TRACE_INVALID_API_ID_RECD      ICF_TRACE_CTU_EVENT + 90
#define ICF_TRACE_SEND_RESP_FAILURE        ICF_TRACE_CTU_EVENT + 91
#define ICF_CFG_TRACE_VMS_GRP_ADDR_PRMS_SET ICF_TRACE_CTU_EVENT + 92
#define ICF_CFG_TRACE_VMS_GRP_PRMS_SET      ICF_TRACE_CTU_EVENT + 93
#define ICF_CFG_TRACE_VMS_LINE_ADDR_PRMS_SET  ICF_TRACE_CTU_EVENT + 94
#define ICF_CFG_TRACE_VMS_LINE_PRMS_SET       ICF_TRACE_CTU_EVENT + 95
               
/* -------------------------------------------------------------------------
 * Hash defined values of the trace ids for CTA service
 * ------------------------------------------------------------------------*/
#define ICF_TRACE_CTA_START                   ICF_CFG_TRACE_VMS_LINE_PRMS_SET
#define ICF_TRACE_CTA_RECVD                   ICF_TRACE_CTA_START + 1
#define ICF_CTA_TRACE_CALL_RESUME_RESP_RECVD  ICF_TRACE_CTA_START + 2
#define ICF_CTA_TRACE_CALL_HOLD_RESP_RECVD    ICF_TRACE_CTA_START + 3
#define ICF_CTA_TRACE_REFER_REQ_SENT          ICF_TRACE_CTA_START + 4
#define ICF_CTA_TRACE_PA_INITIATED_CALL_REL   ICF_TRACE_CTA_START + 5
#define ICF_CTA_TRACE_CC_INITIATED_CALL_REL   ICF_TRACE_CTA_START + 6
#define ICF_TRACE_CTA_STATE                   ICF_TRACE_CTA_START + 7
#define ICF_TRACE_CTA_EVENT                   ICF_TRACE_CTA_START + 8
#define ICF_CTA_TRACE_NOTIFY_RESP_SENT        ICF_TRACE_CTA_START + 9

/* -------------------------------------------------------------------------
 * Hash defined values of the trace ids for RNW service
 * ------------------------------------------------------------------------*/
#define ICF_TRACE_RNW_START  ICF_CTA_TRACE_NOTIFY_RESP_SENT

#define ICF_TRACE_RNW_RECVD                      ICF_TRACE_RNW_START + 1
#define ICF_TRACE_RNW_WITH_REPLACES              ICF_TRACE_RNW_START + 2
#define ICF_TRACE_RNW_NEW_CALL_ID                ICF_TRACE_RNW_START + 3
#define ICF_RNW_TRACE_REFER_RESP_SENT            ICF_TRACE_RNW_START + 4
#define ICF_RNW_TRACE_NOTIFY_SENT                ICF_TRACE_RNW_START + 5
#define ICF_RNW_TRACE_CC_INITIATED_CALL_REL      ICF_TRACE_RNW_START + 6
#define ICF_TRACE_MERGE_IND_SENT                 ICF_TRACE_RNW_START + 7
#define ICF_TRACE_MERGE_MEDIA_SENT               ICF_TRACE_RNW_START + 8
#define ICF_TRACE_REFER_IND_SENT                 ICF_TRACE_RNW_START + 9
#define ICF_RNW_TRACE_NEXT_STATE                 ICF_TRACE_RNW_START + 10
#define ICF_TRACE_RNW_STATE                      ICF_TRACE_RNW_START + 11
#define ICF_TRACE_RNW_EVENT                      ICF_TRACE_RNW_START + 12
                           
/*-----------------------------------------------------------------------------
 * Hash defines for trace ids of CFW service
 * --------------------------------------------------------------------------*/
#define ICF_TRACE_CFW_START  ICF_TRACE_RNW_EVENT
                           
#define ICF_CFW_TRACE_VALIDITY               ICF_TRACE_CFW_START + 1
#define ICF_CFW_TRACE_MSG_SEND               ICF_TRACE_CFW_START + 2
#define ICF_CFW_TRACE_MSG_SEND_FAILURE       ICF_TRACE_CFW_START + 3
#define ICF_CFW_TRACE_FAIL_TO_GET_CFG_DATA   ICF_TRACE_CFW_START + 4
#define ICF_CFW_TRACE_LINE_ID                ICF_TRACE_CFW_START + 5
#define ICF_CFW_TRACE_FAIL_TO_GET_LINE_DATA  ICF_TRACE_CFW_START + 6
#define ICF_CFW_TRACE_CFW_TYPE               ICF_TRACE_CFW_START + 7
#define ICF_CFW_TRACE_CALLING_CFW_ADDR_MATCH ICF_TRACE_CFW_START + 8
#define ICF_CFW_TRACE_INVALID_HOPS           ICF_TRACE_CFW_START + 9
#define ICF_CFW_TRACE_CFW_DIV_ADDR_MATCH     ICF_TRACE_CFW_START + 10
#define ICF_CFW_TRACE_SELF_CFW_ADDR_MATCH    ICF_TRACE_CFW_START + 11
#define ICF_CFW_TRACE_DIV_INFO_PRESENT       ICF_TRACE_CFW_START + 12
#define ICF_CFW_TRACE_DIV_INFO_NOT_PRESENT   ICF_TRACE_CFW_START + 13
#define ICF_CFW_TRACE_DATA_SEND              ICF_TRACE_CFW_START + 14
#define ICF_CFW_TRACE_REL_TYPE_N_CAUSE       ICF_TRACE_CFW_START + 15
#define ICF_CFW_TRACE_STATUS                 ICF_TRACE_CFW_START + 16
#define ICF_CFW_TRACE_INVALID_MSG_ID         ICF_TRACE_CFW_START + 17
#define ICF_CFW_TRACE_INVALID_CFW_TYPE       ICF_TRACE_CFW_START + 18
                           

/*---------------------------------------------------------------------------
 * More Trace for CFG
 * -------------------------------------------------------------------------*/

#define ICF_TRACE_INIT_COMPLETE_RECD ICF_CFW_TRACE_INVALID_CFW_TYPE + 1

/*ICF_CRM_START*/
#define  ICF_TRACE_NETWORK_CONTROLLER_START     ICF_TRACE_INIT_COMPLETE_RECD + 1
#define  ICF_CFG_TRACE_NETWORK_ACTIVATE_RECD    ICF_TRACE_NETWORK_CONTROLLER_START + 1
#define  ICF_CFG_TRACE_NETWORK_DEACTIVATE_RECD  ICF_TRACE_NETWORK_CONTROLLER_START + 2
#define  ICF_TRACE_APPLICATION_START            ICF_CFG_TRACE_NETWORK_DEACTIVATE_RECD
#define  ICF_CFG_TRACE_APP_ADD_RECD    ICF_TRACE_APPLICATION_START + 1
#define  ICF_CFG_TRACE_APP_REMOVE_RECD  ICF_TRACE_APPLICATION_START + 2
/*ICF_CRM_END*/

/* ICF_CONF_STATUS_API_START */
#define  ICF_CFG_TRACE_GET_SYSTEM_SETTINGS_RECD ICF_CFG_TRACE_APP_REMOVE_RECD + 1
#define  ICF_CFG_TRACE_GET_LINE_SETTINGS_RECD   ICF_CFG_TRACE_APP_REMOVE_RECD + 2
/* ICF_CONF_STATUS_API_END */

#define ICF_TRACE_SSA_START                        ICF_CFG_TRACE_GET_LINE_SETTINGS_RECD
#define ICF_TRACE_ENTERED_SSA_PROCESS_MESG         ICF_TRACE_SSA_START + 1
#define ICF_TRACE_APP_POINTER                      ICF_TRACE_SSA_START + 2
#define ICF_TRACE_SSA_BITMASK                      ICF_TRACE_SSA_START + 3
#define ICF_TRACE_TCP_CONN_DB_INDEX                ICF_TRACE_SSA_START + 4
#define ICF_TRACE_TCP_EVENT                        ICF_TRACE_SSA_START + 5
#define ICF_TRACE_STRAY_MSG_RECVD                  ICF_TRACE_SSA_START + 6
#define ICF_TRACE_DEST_MODULE_ID                   ICF_TRACE_SSA_START + 7
#define ICF_TRACE_SIP_METHOD                       ICF_TRACE_SSA_START + 8
#define ICF_TRACE_CALL_LEG_MATCHED                 ICF_TRACE_SSA_START + 9
#define ICF_TRACE_UPDATE_CALL_DET_STATUS           ICF_TRACE_SSA_START + 10
#define ICF_TRACE_SSA_PDB_BITMASK                  ICF_TRACE_SSA_START + 11
#define ICF_TRACE_SSA_CTX_FAILURE_BITMASK          ICF_TRACE_SSA_START + 12
#define ICF_TRACE_SENT_RESP_CODE                   ICF_TRACE_SSA_START + 13
#define ICF_TRACE_TRANSPORT_MODE                   ICF_TRACE_SSA_START + 14
#define ICF_TRACE_TRANSPORT_SCHEME                 ICF_TRACE_SSA_START + 15
#define ICF_TRACE_NUMBER_OF_DIV_HDRS               ICF_TRACE_SSA_START + 16
#define ICF_TRACE_PRIV_HDR_PRESENT                 ICF_TRACE_SSA_START + 17
#define ICF_TRACE_REF_BY_HDR_PRESENT               ICF_TRACE_SSA_START + 18
#define ICF_TRACE_REPLACES_HDR_PRESENT             ICF_TRACE_SSA_START + 19
#define ICF_TRACE_TCP_STATE                        ICF_TRACE_SSA_START + 20
#define ICF_TRACE_TRANS_MODE_REVERT_TO_UDP         ICF_TRACE_SSA_START + 21
#define ICF_TRACE_CONNECT_SENT_WO_SDP              ICF_TRACE_SSA_START + 22
#define ICF_TRACE_OTG_RPR_PRESENT                  ICF_TRACE_SSA_START + 23
#define ICF_TRACE_SIP_METHOD_SENT                  ICF_TRACE_SSA_START + 24
#define ICF_TRACE_SIP_METHOD_RCVD                  ICF_TRACE_SSA_START + 25
#define ICF_TRACE_PRACK_SENT_W_SDP                 ICF_TRACE_SSA_START + 26
#define ICF_TRACE_MED_CHNG_RESP                    ICF_TRACE_SSA_START + 27
#define ICF_TRACE_CALL_HOLD_TYPE                   ICF_TRACE_SSA_START + 28
#define ICF_TRACE_NOTIFY_EVENT                     ICF_TRACE_SSA_START + 29
#define ICF_TRACE_REG_REQ                          ICF_TRACE_SSA_START + 30
#define ICF_TRACE_TIMER_START                      ICF_TRACE_SSA_START + 31
#define ICF_TRACE_TIMER_STOP                       ICF_TRACE_SSA_START + 32
#define ICF_TRACE_TIMER_EXPIRY                     ICF_TRACE_SSA_START + 33
#define ICF_TRACE_SOCKET_CONNECTED                 ICF_TRACE_SSA_START + 34
#define ICF_TRACE_FREE_APP_DATA_CALLED             ICF_TRACE_SSA_START + 35
#define ICF_TRACE_IND_TXN_TIMED_OUT                ICF_TRACE_SSA_START + 36
#define ICF_TRACE_TEL_URL_TO_IP_ADDR               ICF_TRACE_SSA_START + 37
#define ICF_TRACE_REPLACE_NW_CALL_ID               ICF_TRACE_SSA_START + 38
#define ICF_TRACE_VALIDATION_OF_REQ_URI_FAILURE    ICF_TRACE_SSA_START + 39
#define ICF_TRACE_MEDIA_CHANGE_RCVD_W_SDP          ICF_TRACE_SSA_START + 40
#define ICF_TRACE_OPTIONS_RCVD_OUT_OF_DIALOG       ICF_TRACE_SSA_START + 41
#define ICF_TRACE_OPTIONS_USER_NOT_FOUND           ICF_TRACE_SSA_START + 42
#define ICF_TRACE_OPTIONS_USER_BUSY                ICF_TRACE_SSA_START + 43
#define ICF_TRACE_SUBSCRIBE_EVENT_PACKAGE          ICF_TRACE_SSA_START + 44
#define ICF_TRACE_SUBSCRIBE_RESP                   ICF_TRACE_SSA_START + 45
#define ICF_TRACE_NOTIFY_RCVD                      ICF_TRACE_SSA_START + 46
#define ICF_TRACE_INFO_RCVD_W_PAYLOAD              ICF_TRACE_SSA_START + 47
#define ICF_TRACE_SUPPORTED_100_REL_PRESENT        ICF_TRACE_SSA_START + 48

#define ICF_TRACE_REQUIRE_PRECONDITION_PRESENT	   ICF_TRACE_SSA_START + 49
#define ICF_TRACE_NOTIFY_RCVD_N_CTXT_DELINKED      ICF_TRACE_SSA_START + 50
#define ICF_TRACE_PHONE_CTXT_RECVD                 ICF_TRACE_SSA_START + 51
#define ICF_TRACE_MSG_TYPE_N_STATE_IN_OVLAP_TXN    ICF_TRACE_SSA_START + 52
#define ICF_TRACE_EXIT_PROCESS_MESG                ICF_TRACE_SSA_START + 53

#define ICF_SIP_STACK_BRIEF_TRACE                  ICF_TRACE_SSA_START + 54
#define ICF_SIP_STACK_DETAILED_TRACE               ICF_TRACE_SSA_START + 55
#define ICF_SIP_STACK_DEBUG_TRACE                  ICF_TRACE_SSA_START + 56

#define  ICF_TRACE_ERROR_BASE                      ICF_SIP_STACK_DEBUG_TRACE + 1
#define  ICF_MAX_NUM_OF_TRACE_IDS                  ICF_TRACE_ERROR_BASE

#define	ICF_CFG_TRACE_SELF_ID_PRMS_RECD	    ICF_CFG_TRACE_SELF_ID_PRMS_REQ_RECD



/*******************************************************************
 *
 * Trace Ids to be reported to Application
 *
 *******************************************************************/


/*-----------------------------------------------------------------------------
 * Hash defines for trace ids of Interface Type
 * --------------------------------------------------------------------------*/

#define ICF_INTERFACE_TRACE_START       0
#define ICF_TRACE_SIP_PDU               ICF_INTERFACE_TRACE_START
#define ICF_TRACE_APP_MESG              ICF_INTERFACE_TRACE_START + 1
#define ICF_TRACE_MEDIA_MESG            ICF_INTERFACE_TRACE_START + 2
#define ICF_INTERFACE_TRACE_END         ICF_TRACE_MEDIA_MESG


/*-----------------------------------------------------------------------------
 * Hash defines for trace ids of Configuration Type
 * --------------------------------------------------------------------------*/

#define ICF_CONFIGURATION_TRACE_START   ICF_INTERFACE_TRACE_END
#define ICF_TRACE_APP_ADD               ICF_CONFIGURATION_TRACE_START + 1
#define ICF_TRACE_USER_INFO             ICF_CONFIGURATION_TRACE_START + 2
#define ICF_TRACE_SELF_TRANSPORT_ADDR   ICF_CONFIGURATION_TRACE_START + 3
#define ICF_TRACE_PROXY_INFO            ICF_CONFIGURATION_TRACE_START + 4
#define ICF_TRACE_REGISTRAR_INFO        ICF_CONFIGURATION_TRACE_START + 5
#define ICF_TRACE_SYSTEM_RESTARTING     ICF_CONFIGURATION_TRACE_START + 6
#define ICF_TRACE_SYSTEM_REINITIALISING ICF_CONFIGURATION_TRACE_START + 7
/* Primary proxy server becomes active */
#define ICF_TRACE_PRIMARY_PROXY_SERVER_ACTIVE      ICF_CONFIGURATION_TRACE_START + 8
/* Secondary proxy server becomes active */
#define ICF_TRACE_SECONDARY_PROXY_SERVER_ACTIVE    ICF_CONFIGURATION_TRACE_START + 9
/* Primary DNS Server becomes active */
#define ICF_TRACE_PRIMARY_DNS_SERVER_ACTIVE        ICF_CONFIGURATION_TRACE_START + 10
/* Secondary DNS Server becomes active */
#define ICF_TRACE_SECONDARY_DNS_SERVER_ACTIVE      ICF_CONFIGURATION_TRACE_START + 11
/* Primary DNS Server is not responding */
#define ICF_TRACE_PRIMARY_DNS_SERVER_NOT_CONFIGURED        ICF_CONFIGURATION_TRACE_START + 15
/* Secondary DNS Server present so primary cannot be deleted */
#define ICF_TRACE_SECONDARY_DNS_SERVER_PRESENT             ICF_CONFIGURATION_TRACE_START + 17
/* Proxy is already configured so DHCP Server cannot be configured */
#define ICF_TRACE_PROXY_SERVER_ALREADY_CONFIGURED          ICF_CONFIGURATION_TRACE_START + 18

/* DHCP Server address is already configured */
#define ICF_TRACE_DHCP_SERVER_ALREADY_CONFIGURED           ICF_CONFIGURATION_TRACE_START + 19
/* DHCP Server address cannot be deleted */
#define ICF_TRACE_DHCP_SERVER_CANNOT_BE_DELETED            ICF_CONFIGURATION_TRACE_START + 20
#define ICF_TRACE_DHCP_FAILURE                             ICF_CONFIGURATION_TRACE_START + 21
#define ICF_TRACE_SEC_PROXY_INFO		                   ICF_CONFIGURATION_TRACE_START + 22
#define ICF_TRACE_PCSCF_UNREACHABLE                        ICF_CONFIGURATION_TRACE_START + 23
/* Primary proxy not responding */
#define ICF_TRACE_PRIMARY_PROXY_NOT_RESPONDING             ICF_CONFIGURATION_TRACE_START + 24
/* Secondary proxy not responding */
#define ICF_TRACE_SECONDARY_PROXY_NOT_RESPONDING           ICF_CONFIGURATION_TRACE_START + 25
#define ICF_TRACE_PRIMARY_DNS_SERVER_NOT_RESPONDING        ICF_CONFIGURATION_TRACE_START + 26
#define ICF_TRACE_SEC_REGISTRAR_INFO                       ICF_CONFIGURATION_TRACE_START + 27
#define ICF_TRACE_SECONDARY_DNS_SERVER_NOT_RESPONDING        ICF_CONFIGURATION_TRACE_START + 28
#define ICF_TRACE_DISCOVERED_PROXY_ADDRESS_FROM_DHCP        ICF_CONFIGURATION_TRACE_START + 29
#define ICF_CONFIGURATION_TRACE_END                        ICF_TRACE_DISCOVERED_PROXY_ADDRESS_FROM_DHCP 

/*-----------------------------------------------------------------------------
 * Hash defines for trace ids of Registration Type
 * --------------------------------------------------------------------------*/

#define ICF_REGISTRATION_TRACE_START    ICF_CONFIGURATION_TRACE_END
#define ICF_TRACE_REGISTARTION_REQ      ICF_REGISTRATION_TRACE_START + 1
#define ICF_TRACE_DEREG_REQ             ICF_REGISTRATION_TRACE_START + 2
#define ICF_TRACE_REG_RESP              ICF_REGISTRATION_TRACE_START + 3
#define ICF_TRACE_REREG_REQ             ICF_REGISTRATION_TRACE_START + 4
#define ICF_TRACE_REG_AUTH_401          ICF_REGISTRATION_TRACE_START + 5
#define ICF_TRACE_REG_AUTH_407          ICF_REGISTRATION_TRACE_START + 6
#define ICF_TRACE_REG_TIMER_EXPIRE      ICF_REGISTRATION_TRACE_START + 7
#define ICF_TRACE_REG_EVENT_SUBS_REQ    ICF_REGISTRATION_TRACE_START + 8
#define ICF_TRACE_REG_EVENT_SUBS_RESP    ICF_REGISTRATION_TRACE_START + 9
/* Primary Registrar is now active */
#define ICF_TRACE_PRIMARY_REGISTRAR_ACTIVE \
                                        ICF_REGISTRATION_TRACE_START + 10
/* Secondary Registrar is now active */
#define ICF_TRACE_SECONDARY_REGISTRAR_ACTIVE \
                                        ICF_REGISTRATION_TRACE_START + 11
/* Primary Registrar not responding */
#define ICF_TRACE_PRIMARY_REGISTRAR_NOT_RESPONDING \
                                        ICF_REGISTRATION_TRACE_START + 12
/* Secondary Registrar not responding */
#define ICF_TRACE_SECONDARY_REGISTRAR_NOT_RESPONDING \
                                        ICF_REGISTRATION_TRACE_START + 13
#define ICF_TRACE_REG_AKA_AUTH_SUCCESS  ICF_REGISTRATION_TRACE_START + 14
#define ICF_TRACE_REG_GUARD_TIMER_EXPIRY  ICF_REGISTRATION_TRACE_START + 15
#define ICF_REGISTRATION_TRACE_END      ICF_TRACE_REG_GUARD_TIMER_EXPIRY 


/*-----------------------------------------------------------------------------
 * Hash defines for trace ids of Subscription Type
 * --------------------------------------------------------------------------*/

#define ICF_SUBSCRIPTION_TRACE_START    ICF_REGISTRATION_TRACE_END
#define ICF_TRACE_SUBSCRIPTION_REQ      ICF_SUBSCRIPTION_TRACE_START + 1
#define ICF_TRACE_SUBS_AUTH_401         ICF_SUBSCRIPTION_TRACE_START + 2
#define ICF_TRACE_SUBS_AUTH_407         ICF_SUBSCRIPTION_TRACE_START + 3
#define ICF_TRACE_UNSUBS_REQ            ICF_SUBSCRIPTION_TRACE_START + 4
#define ICF_TRACE_SUBS_RESP             ICF_SUBSCRIPTION_TRACE_START + 5
#define ICF_TRACE_NOTIFY_FOR_SUBS       ICF_SUBSCRIPTION_TRACE_START + 6
#define ICF_TRACE_OTDLG_NOTIFY_IND      ICF_SUBSCRIPTION_TRACE_START + 7
#define ICF_TRACE_NOTIFY_CFM            ICF_SUBSCRIPTION_TRACE_START + 8
#define ICF_TRACE_RESUBS                ICF_SUBSCRIPTION_TRACE_START + 9
#define ICF_TRACE_SUBS_TIMER_EXPIRE     ICF_SUBSCRIPTION_TRACE_START + 10
/* The following trace is issued to the application on expiry of 
   await notify cfm timer. This is applicable only when application
   has enabled support of asynchronous NOTIFY
 */
#define ICF_TRACE_NOTIFY_CFM_TIMER_EXPIRE ICF_SUBSCRIPTION_TRACE_START + 11
#define ICF_SUBSCRIPTION_TRACE_END      ICF_TRACE_NOTIFY_CFM_TIMER_EXPIRE

/*-----------------------------------------------------------------------------
 * Hash defines for trace ids of Call Control - Options Type
 * --------------------------------------------------------------------------*/

#define ICF_CALL_CONTROL_TRACE_START    ICF_SUBSCRIPTION_TRACE_END
#define ICF_TRACE_INC_OPTIONS           ICF_CALL_CONTROL_TRACE_START + 1
#define ICF_TRACE_INC_OPTIONS_RESP      ICF_CALL_CONTROL_TRACE_START + 2
#define ICF_TRACE_OTG_OPTIONS           ICF_CALL_CONTROL_TRACE_START + 3
#define ICF_TRACE_OTG_OPTIONS_RESP      ICF_CALL_CONTROL_TRACE_START + 4
#define ICF_TRACE_MEDIA_CAPABILITY      ICF_CALL_CONTROL_TRACE_START + 5


/*-----------------------------------------------------------------------------
 * Hash defines for trace ids of Call Control - Info Type
 * --------------------------------------------------------------------------*/

#define ICF_TRACE_INC_INFO              ICF_CALL_CONTROL_TRACE_START + 6
#define ICF_TRACE_INC_INFO_RESP         ICF_CALL_CONTROL_TRACE_START + 7
#define ICF_TRACE_OTG_INFO              ICF_CALL_CONTROL_TRACE_START + 8
#define ICF_TRACE_OTG_INFO_RESP         ICF_CALL_CONTROL_TRACE_START + 9


/*-----------------------------------------------------------------------------
 * Hash defines for trace ids of Call Control - 2 Party Call Type
 * --------------------------------------------------------------------------*/

#define ICF_TRACE_CALL_CONNECTED        ICF_CALL_CONTROL_TRACE_START + 10
#define ICF_TRACE_CREATE_CALL_REQ       ICF_CALL_CONTROL_TRACE_START + 11
#define ICF_TRACE_INCOMING_CALL_IND     ICF_CALL_CONTROL_TRACE_START + 12
#define ICF_TRACE_INVITE_SENT           ICF_CALL_CONTROL_TRACE_START + 13
#define ICF_TRACE_INVITE_RECVD          ICF_CALL_CONTROL_TRACE_START + 14
#define ICF_TRACE_EARLY_INC_CALL_IND    ICF_CALL_CONTROL_TRACE_START + 15
#define ICF_TRACE_EARLY_INC_CALL_CFM    ICF_CALL_CONTROL_TRACE_START + 16
#define ICF_TRACE_LOCAL_SDP_OFFER       ICF_CALL_CONTROL_TRACE_START + 17
#define ICF_TRACE_REMOTE_SDP_OFFER      ICF_CALL_CONTROL_TRACE_START + 18
#define ICF_TRACE_LOCAL_SDP_ANSWER      ICF_CALL_CONTROL_TRACE_START + 19
#define ICF_TRACE_REMOTE_SDP_ANSWER     ICF_CALL_CONTROL_TRACE_START + 20
#define ICF_TRACE_CODEC_RESERVE         ICF_CALL_CONTROL_TRACE_START + 21
#define ICF_TRACE_RTP_ADDR_ALLOCATE     ICF_CALL_CONTROL_TRACE_START + 22
#define ICF_TRACE_STREAM_CREATE         ICF_CALL_CONTROL_TRACE_START + 23
#define ICF_TRACE_STREAM_MODIFY         ICF_CALL_CONTROL_TRACE_START + 24
#define ICF_TRACE_CODEC_COMMIT          ICF_CALL_CONTROL_TRACE_START + 25
#define ICF_TRACE_STREAM_DELETE         ICF_CALL_CONTROL_TRACE_START + 26
#define ICF_TRACE_RTP_ADDR_DEALLOCATE   ICF_CALL_CONTROL_TRACE_START + 27
#define ICF_TRACE_CODEC_RELEASE         ICF_CALL_CONTROL_TRACE_START + 28
#define ICF_TRACE_ALERT_FROM_APP        ICF_CALL_CONTROL_TRACE_START + 29
#define ICF_TRACE_ALERT_TO_APP          ICF_CALL_CONTROL_TRACE_START + 30
#define ICF_TRACE_MEDIA_CONNECT_FROM_APP   ICF_CALL_CONTROL_TRACE_START + 31
#define ICF_TRACE_MEDIA_CONNECT_TO_APP  ICF_CALL_CONTROL_TRACE_START + 32
#define ICF_TRACE_183_SENT              ICF_CALL_CONTROL_TRACE_START + 33
#define ICF_TRACE_180_SENT              ICF_CALL_CONTROL_TRACE_START + 34
#define ICF_TRACE_183_RECVD             ICF_CALL_CONTROL_TRACE_START + 35
#define ICF_TRACE_180_RECVD             ICF_CALL_CONTROL_TRACE_START + 36
#define ICF_TRACE_100_SENT              ICF_CALL_CONTROL_TRACE_START + 37
#define ICF_TRACE_100_RECVD             ICF_CALL_CONTROL_TRACE_START + 38
#define ICF_TRACE_PROVISIONAL_RESP_SENT ICF_CALL_CONTROL_TRACE_START + 39
#define ICF_TRACE_PROVISIONAL_RESP_RECVD   ICF_CALL_CONTROL_TRACE_START + 40
#define ICF_TRACE_200_SENT              ICF_CALL_CONTROL_TRACE_START + 41
#define ICF_TRACE_200_RECVD             ICF_CALL_CONTROL_TRACE_START + 42
#define ICF_TRACE_FAILURE_RESP_SENT     ICF_CALL_CONTROL_TRACE_START + 43
#define ICF_TRACE_FAILURE_RESP_RECVD    ICF_CALL_CONTROL_TRACE_START + 44
#define ICF_TRACE_202_SENT              ICF_CALL_CONTROL_TRACE_START + 45
#define ICF_TRACE_202_RECVD             ICF_CALL_CONTROL_TRACE_START + 46
#define ICF_TRACE_PRACK_RECVD           ICF_CALL_CONTROL_TRACE_START + 47
#define ICF_TRACE_PRACK_SENT            ICF_CALL_CONTROL_TRACE_START + 48
#define ICF_TRACE_UPDATE_RECVD          ICF_CALL_CONTROL_TRACE_START + 49
#define ICF_TRACE_UPDATE_SENT           ICF_CALL_CONTROL_TRACE_START + 50
#define ICF_TRACE_REINVITE_RECVD        ICF_CALL_CONTROL_TRACE_START + 51
#define ICF_TRACE_REINVITE_SENT         ICF_CALL_CONTROL_TRACE_START + 52
#define ICF_TRACE_CALL_TERMINATION_INITIATED    ICF_CALL_CONTROL_TRACE_START + 55
#define ICF_TRACE_CALL_CANCELLATION_INITIATED   ICF_CALL_CONTROL_TRACE_START + 56
#define ICF_TRACE_CALL_MODIFY_IND       ICF_CALL_CONTROL_TRACE_START + 57
#define ICF_TRACE_CALL_MODIFY_REQ       ICF_CALL_CONTROL_TRACE_START + 58
#define ICF_TRACE_CALL_MODIFY_RESP      ICF_CALL_CONTROL_TRACE_START + 59
#define ICF_TRACE_CALL_MODIFY_CFM       ICF_CALL_CONTROL_TRACE_START + 60


/*-----------------------------------------------------------------------------
 * Hash defines for trace ids of Call Control - Fax Type
 * --------------------------------------------------------------------------*/

#define ICF_TRACE_START_FAX_TO_APP      ICF_CALL_CONTROL_TRACE_START + 61
#define ICF_TRACE_START_FAX_FROM_APP    ICF_CALL_CONTROL_TRACE_START + 62
#define ICF_TRACE_START_FAX_RESP_TO_APP         ICF_CALL_CONTROL_TRACE_START + 63
#define ICF_TRACE_STOP_FAX_TO_APP       ICF_CALL_CONTROL_TRACE_START + 64
#define ICF_TRACE_STOP_FAX_FROM_APP     ICF_CALL_CONTROL_TRACE_START + 65
#define ICF_TRACE_STOP_FAX_RESP_TO_APP          ICF_CALL_CONTROL_TRACE_START + 66
/*-----------------------------------------------------------------------------
 * Hash defines for trace ids of Call Control - Service Type
 * --------------------------------------------------------------------------*/

#define ICF_TRACE_STREAM_MERGE          ICF_CALL_CONTROL_TRACE_START + 67
#define ICF_TRACE_CONFERENCE_REQ        ICF_CALL_CONTROL_TRACE_START + 68
#define ICF_TRACE_PARTY_REPLACED_IND    ICF_CALL_CONTROL_TRACE_START + 69
#define ICF_TRACE_REFER_RECVD           ICF_CALL_CONTROL_TRACE_START + 70
#define ICF_TRACE_REFER_SENT            ICF_CALL_CONTROL_TRACE_START + 71
#define ICF_TRACE_CTA_REQ               ICF_CALL_CONTROL_TRACE_START + 72
#define ICF_TRACE_CTU_REQ               ICF_CALL_CONTROL_TRACE_START + 73
#define ICF_TRACE_CALL_HOLD_REQ         ICF_CALL_CONTROL_TRACE_START + 74
#define ICF_TRACE_CALL_RESUME_REQ       ICF_CALL_CONTROL_TRACE_START + 75
#define ICF_TRACE_CTA_RESP              ICF_CALL_CONTROL_TRACE_START + 76
#define ICF_TRACE_CTU_RESP              ICF_CALL_CONTROL_TRACE_START + 77
#define ICF_TRACE_CALL_HOLD_RESP        ICF_CALL_CONTROL_TRACE_START + 78
#define ICF_TRACE_CALL_RESUME_RESP      ICF_CALL_CONTROL_TRACE_START + 79
#define ICF_TRACE_REMOTE_CALL_TRANSFER_CFM      ICF_CALL_CONTROL_TRACE_START + 80
#define ICF_TRACE_302_SENT              ICF_CALL_CONTROL_TRACE_START + 81
#define ICF_TRACE_302_RECVD             ICF_CALL_CONTROL_TRACE_START + 82
#define ICF_TRACE_CONFERENCE_RESP       ICF_CALL_CONTROL_TRACE_START + 83
#define ICF_TRACE_CALL_INITIATED_FOR_INC_REFER  ICF_CALL_CONTROL_TRACE_START + 84
#define ICF_TRACE_NOTIFY_FOR_REFER_RECVD        ICF_CALL_CONTROL_TRACE_START + 85
#define ICF_TRACE_NOTIFY_FOR_REFER_SENT         ICF_CALL_CONTROL_TRACE_START + 86
#define ICF_TRACE_CALL_WAITING_IND              ICF_CALL_CONTROL_TRACE_START + 87


/*-----------------------------------------------------------------------------
 * Hash defines for trace ids of Timer Type
 * --------------------------------------------------------------------------*/

#define ICF_TRACE_SETUP_TIMER_EXPIRE            ICF_CALL_CONTROL_TRACE_START + 88
#define ICF_TRACE_ALERTING_TIMER_EXPIRE         ICF_CALL_CONTROL_TRACE_START + 89
#define ICF_TRACE_RELEASE_TIMER_EXPIRE          ICF_CALL_CONTROL_TRACE_START + 90
#define ICF_TRACE_MEDIA_TIMER_EXPIRE            ICF_CALL_CONTROL_TRACE_START + 91
#define ICF_TRACE_CALL_HOLD_RESUME_TIMER_EXPIRE ICF_CALL_CONTROL_TRACE_START + 92
#define ICF_TRACE_CTU_TIMER_EXPIRE              ICF_CALL_CONTROL_TRACE_START + 93
#define ICF_TRACE_CTA_TIMER_EXPIRE              ICF_CALL_CONTROL_TRACE_START + 94
#define ICF_TRACE_CONF_TIMER_EXPIRE             ICF_CALL_CONTROL_TRACE_START + 95
#define ICF_TRACE_OPTIONS_TIMER_EXPIRE          ICF_CALL_CONTROL_TRACE_START + 96
#define ICF_TRACE_INFO_TIMER_EXPIRE             ICF_CALL_CONTROL_TRACE_START + 97
#define ICF_TRACE_BYE_SENT                      ICF_CALL_CONTROL_TRACE_START + 98
#define ICF_TRACE_BYE_RECVD                     ICF_CALL_CONTROL_TRACE_START + 99
#define ICF_TRACE_ACK_SENT                          ICF_CALL_CONTROL_TRACE_START + 100
#define ICF_TRACE_ACK_RECVD             ICF_CALL_CONTROL_TRACE_START + 101
#define ICF_TRACE_CANCEL_SENT                   ICF_CALL_CONTROL_TRACE_START + 102
#define ICF_TRACE_CANCEL_RECVD          ICF_CALL_CONTROL_TRACE_START + 103
#define ICF_TRACE_SDP_RTP_AVP_RECVD             ICF_CALL_CONTROL_TRACE_START + 104
#define ICF_TRACE_SDP_RTP_SAVP_RECVD            ICF_CALL_CONTROL_TRACE_START + 105

#define ICF_TRACE_OTG_PUBLISH           ICF_CALL_CONTROL_TRACE_START + 106
#define ICF_TRACE_OTG_PUBLISH_RESP      ICF_CALL_CONTROL_TRACE_START + 107
/*   Trace will be sent to application when Early session ind will be sent
     To application */
#define ICF_TRACE_EARLY_SESSION_IND     ICF_CALL_CONTROL_TRACE_START + 111
/*  Trace will be sent to application when Early session cfm will be received
     from application */
#define ICF_TRACE_EARLY_SESSION_CFM     ICF_CALL_CONTROL_TRACE_START + 112
/* Tunnel mode specific traces for new MM APIs */    
#define ICF_TRACE_TUNNELLED_CMS_REQ_SENT     ICF_CALL_CONTROL_TRACE_START + 113
#define ICF_TRACE_TUNNELLED_CMS_RESP_RECVD   ICF_CALL_CONTROL_TRACE_START + 114
#define ICF_TRACE_TUNNELLED_MMS_RESP_RECVD   ICF_CALL_CONTROL_TRACE_START + 115
#define ICF_TRACE_TUNNELLED_MMS_REQ_SENT     ICF_CALL_CONTROL_TRACE_START + 116
/*  CALL control traces for Prack enhancements */
#define ICF_TRACE_PRACK_REQ_RECV_IND_TO_APP  ICF_CALL_CONTROL_TRACE_START + 117
#define ICF_TRACE_PRACK_REQ_SENT_IND_TO_APP  ICF_CALL_CONTROL_TRACE_START + 118
#define ICF_TRACE_PRACK_RESP_RECV_IND_TO_APP ICF_CALL_CONTROL_TRACE_START + 119
#define ICF_TRACE_PRACK_RESP_SENT_IND_TO_APP ICF_CALL_CONTROL_TRACE_START + 120

#define ICF_CALL_CONTROL_TRACE_END           ICF_TRACE_PRACK_RESP_SENT_IND_TO_APP
/* ASYNCHRONUS_MESSAGE enhancements */
#define ICF_MESSAGE_CONTROL_TRACE_START         ICF_CALL_CONTROL_TRACE_END

#define ICF_TRACE_OUT_OF_DIALOG_MESSAGE_RECVD   ICF_MESSAGE_CONTROL_TRACE_START + 1
#define ICF_TRACE_OUT_OF_DIALOG_MESSAGE_SENT    ICF_MESSAGE_CONTROL_TRACE_START + 2
#define ICF_TRACE_INC_MESSAGE                   ICF_MESSAGE_CONTROL_TRACE_START + 3
#define ICF_TRACE_OTG_MESSAGE                   ICF_MESSAGE_CONTROL_TRACE_START + 4
#define ICF_TRACE_OTG_MESSAGE_RESP              ICF_MESSAGE_CONTROL_TRACE_START + 5
#define ICF_TRACE_MESSAGE_CFM_TIMER_EXPIRE      ICF_MESSAGE_CONTROL_TRACE_START + 6
#define ICF_TRACE_MESSAGE_CFM			        ICF_MESSAGE_CONTROL_TRACE_START + 7

#define ICF_MESSAGE_CONTROL_TRACE_END			ICF_TRACE_MESSAGE_CFM




/*-----------------------------------------------------------------------------
 * Hash defines for trace ids of Error Type
 * --------------------------------------------------------------------------*/

#define ICF_ERROR_TRACE_START                   ICF_MESSAGE_CONTROL_TRACE_END
#define ICF_TRACE_SIP_MSG_RETRANSMISSION_TIMEOUT        ICF_ERROR_TRACE_START + 1
#define ICF_TRACE_DNS_QUERY_FAILURE             ICF_ERROR_TRACE_START + 2
#define ICF_TRACE_STACK_ERROR                   ICF_ERROR_TRACE_START + 3
#define ICF_TRACE_SOCKET_ERROR                  ICF_ERROR_TRACE_START + 4
#define ICF_TRACE_UDP_SEND_ERROR                ICF_ERROR_TRACE_START + 5
#define ICF_TRACE_UDP_RECV_ERROR                ICF_ERROR_TRACE_START + 6
#define ICF_TRACE_TCP_SEND_ERROR                ICF_ERROR_TRACE_START + 7
#define ICF_TRACE_TCP_RECV_ERROR                ICF_ERROR_TRACE_START + 8
#define ICF_TRACE_TLS_SEND_ERROR                ICF_ERROR_TRACE_START + 9
#define ICF_TRACE_TLS_RECV_ERROR                ICF_ERROR_TRACE_START + 10
#define ICF_TRACE_MEMGET_ERROR                  ICF_ERROR_TRACE_START + 11
#define ICF_TRACE_MEMFREE_ERROR                 ICF_ERROR_TRACE_START + 12
#define ICF_TRACE_START_TIMER_ERROR             ICF_ERROR_TRACE_START + 13
#define ICF_TRACE_STOP_TIMER_ERROR              ICF_ERROR_TRACE_START + 14
#define ICF_TRACE_DMS_IND                       ICF_ERROR_TRACE_START + 15
#define ICF_TRACE_SRTP_NEG_FAILURE              ICF_ERROR_TRACE_START + 16
#define ICF_TRACE_AKA_AUTH_FAIL                 ICF_ERROR_TRACE_START + 17
#define ICF_TRACE_INVALID_AKA_AUTH_STATUS       ICF_ERROR_TRACE_START + 18
#define ICF_TRACE_INVALID_ASSOC_URI             ICF_ERROR_TRACE_START + 19 
#define ICF_ERROR_TRACE_END                     ICF_TRACE_INVALID_ASSOC_URI
    


/*-----------------------------------------------------------------------------
 * Hash defines for trace ids of System Type
 * --------------------------------------------------------------------------*/

#define ICF_SYSTEM_TRACE_START                  ICF_ERROR_TRACE_END
#define ICF_TRACE_TCP_CONNECTION_OPEN           ICF_SYSTEM_TRACE_START + 1
#define ICF_TRACE_TCP_CONNECTION_CLOSE          ICF_SYSTEM_TRACE_START + 2
#define ICF_TRACE_TLS_CONNECTION_OPEN           ICF_SYSTEM_TRACE_START + 3
#define ICF_TRACE_TLS_CONNECTION_CLOSE          ICF_SYSTEM_TRACE_START + 4
#define ICF_TRACE_UDP_SERVER_OPEN               ICF_SYSTEM_TRACE_START + 5
#define ICF_TRACE_UDP_SERVER_CLOSE              ICF_SYSTEM_TRACE_START + 6
#define ICF_TRACE_TCP_SERVER_OPEN               ICF_SYSTEM_TRACE_START + 7
#define ICF_TRACE_TCP_SERVER_CLOSE              ICF_SYSTEM_TRACE_START + 8
#define ICF_TRACE_TLS_SERVER_OPEN               ICF_SYSTEM_TRACE_START + 9
#define ICF_TRACE_TLS_SERVER_CLOSE              ICF_SYSTEM_TRACE_START + 10
#define ICF_TRACE_SRTP_FALLBACK_INVOCATION      ICF_SYSTEM_TRACE_START + 11
#define ICF_SYSTEM_TRACE_END                    ICF_SYSTEM_TRACE_START + 12
#define ICF_MAX_APP_TRACE_IDS                   ICF_SYSTEM_TRACE_END

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* End of __ICF_TRACE_ID_H__ */

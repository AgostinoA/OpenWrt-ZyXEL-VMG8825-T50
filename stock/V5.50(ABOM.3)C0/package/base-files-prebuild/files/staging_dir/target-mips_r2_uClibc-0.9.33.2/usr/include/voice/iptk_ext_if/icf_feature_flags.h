/******************************************************************************
**
** FILE NAME: icf_feature_flags.h
**
*******************************************************************************
**
** DESCRIPTION: This file contains the FEATURE FLAGS of IMS_CLIENT FRAMEWORK. 
**
** DATE        NAME            REFERENCE    REASON
** ----        ----            ---------    ------
** 23-08-05   Ashutos Rath     ICF_LLD   Creating a common Feature flag
**                                          for enabling various feature of
**                                          IMS CLIENT FRAME WORK
** 04-10-05   Ashutos Rath     ICF_LLD   ICF_SIGCOMP_SUPPORT Flag Made On 
**                                       by default.
** 29-11-05	  Kirti Dhingra              ICF_QOS_SUPPORT Flag added and Made 
**        								 on by default. 
** 07-12-2005 Rohit Aggarwal   ICF 4.0   Flags for IPSec support
**                                     
** 27-Nov-2006 Deepti Goyal    ICF 6.2   ICF Nat feature support
**
** 22-Aug-2007 Deepti Goyal    ICF 6.5   A new flag for DNS Name Server configurtion
**
** 17-Jan-2008 Neha Gupta      SPR 18033 New flag for func_fail_ut_simulation
** 28-Jan-2008 Kamini Gangwani Rel 8.0   Remove IMS_CLIENT and 
**                                       NON_IMS_CLIENT flags  
** 12-Apr-2008 Alok Tiwari     KW IPTK 8.0 New flag added for klocwork 
**                                         FALSE_POSITIVE warnings.
** 24-Nov-2008 Rajiv Kumar     SPR 19188 Added new flag for INTEROP specific
**                                       chg (Merging of Rel 7.1.2 SPR)
** 01-Sep-2009 Tarun Gupta     SPR 20008 Added a new flag for memory profiling
** Copyright (c) 2007, Aricent.
******************************************************************************/

#ifndef _ICF_FEATURE_FLAGS_H_
#define _ICF_FEATURE_FLAGS_H_

/****************************************************************************/
/*****USER CONFIGURATION OF COMPILE TIME FEATURE FLAGS BEGINS HERE***********/
/****************************************************************************/
/*#define ICF_LOAD_STAT*/

/*FLAG to enable the interop specific code changes */
/*By default this flag is not define on main line.*/
/*#define IPTK_INTEROP_SPECIFIC_CHANGE   0*/

/* Flag to determine whether the req-uri of Incoming INVITE needs to be parsed
 * to check if alternate address formats can be generated.
 */
#define ICF_REQ_URI_ALTERNATE_ADDR_PARSING 1

/*#define ICF_REQ_URI_CALLED_PARTY_ADDR_PARSING 1*/

/* The approach in this flag has been discarded */
/* Flag to determine whether the req-uri of Incoming INVITE needs to be parsed
 * to check if alternate address formats can be generated.
 */

#define ICF_LOOPBACK_SUPPORT 1 

#define ICF_DNS_LOOKUP_ENABLED      1
#ifdef ICF_DNS_LOOKUP_ENABLED
/* Flag to determine that the DNS server address can be changed at runtime. 
 * So ICF will read the DNS server address for each DNS query
 */
#define ICF_RUNTIME_NAMESERVER_CONFIG  1
#endif

#define ICF_STAT_ENABLE            1

#ifndef ICF_LOAD_STAT
/* Flag for Enabling Traces */
/* Comment this Flag to Disable Trace */ 
#define ICF_TRACE_ENABLE             1
#define ICF_UNIQUE_CALL_ID_CHANGES   1
/* Flag to get detailed function enter exit traces */
#define ICF_DETAILED_DEBUG_TRACE 1 
#define ICF_INTERFACE_TRACE_ENABLE 1
#endif

/* Flag for Enabling Error Reporting */
/* Comment this Flag to Disabel Error reporting*/
#define ICF_ERROR_ENABLE            1

/* Flag to enabling Session timer compile time option*/
/* Comment this Flag to Disable Session Timer Feature */
#define ICF_SESSION_TIMER			1

/* Flag to enabling Voice call Services like Call Hold/Resume etc*/
/* Comment this Flag to Disable ICF Service Layer */
#define ICF_SERVICE_ENABLE          1

/* adding compile time flag for Licensing in ICF */
/* #define ICF_LICENSE_ENABLE          1 */

/*********************************************************************/
/* IMS specific Feature Flag: USER SHOULD NOT SWITCH ON THIS FLAG
 * IF ICF IS MEANT FOR IPphone client Framework*/
/*********************************************************************/
/* Flag for ICF NETWORK ACTIVATION*/
/* TBD */
/*#define ICF_NW_ACTIVATE                  1*/
#ifdef ICF_ENABLE_TLS /*ZyXEL,Jason,SIP over TLS*/ 
 #define ICF_SECURE_SUPPORT              1 
#endif
#define ICF_QOS_STUBBED_OUT	     1
/****************************************************************************/
/*****USER CONFIGURATION OF COMPILE TIME FEATURE FLAGS END HERE**************/
/*****USER SHOULD ABSTAIN FROM CONFIGURING COMPILE TIME FEATURE FLAGS *******/
/**********************BEYOND THIS POINT*************************************/
#define ICF_FAX_SUPPORT                  1

#define ICF_FAX_PASS_THROUGH		 1
/* Enable this flag for platform testing */
/*#define ICF_PLTFM_TEST_ENABLE			1*/

/* Enable this flag PCSCSF Discovery  */
/* #define ICF_P_CSCF_DISCOVERY_ENABLED		1 */
/* Enable this flag for NAT support in ICF */

/* #define ICF_NAT_TRAVERSAL     1  */

#ifdef ICF_NAT_TRAVERSAL

/* Enable this flag to support rport for NAT signalling.
   "rport" will be send in the Via Header of SIP request messages.
 */
#define ICF_NAT_RPORT_SUPPORT    1

/* Enable this flag to support the NAT traversal for media as well.
   Enabling this flag will allow the messages to be send/recv to/from NAT
   library.
 */
#define ICF_NAT_MEDIA_TRAVERSAL  1

/* Enable this flag to support the RTCP attribute as a line in SDP.
 */
#define ICF_RTCP_ATTR_SUPPORT    1

#endif

/*Enable this  flag to print the  ICF API*/

/*#define ICF_LOAD_DEBUG 1*/
/*#define ICF_LOAD_FORCEFUL_CALL_CLEAR 1*/

/*#define ICF_UT_TEST		1*/
/*#define ICF_KLOCWORK_SHOW_FALSE_POSITIVE 1*/

/* SPR 20008 : The following macro should be defined only for memory profiling
   puprposes.
*/   
/* #define ICF_DEBUG_MEMPOOL 1 */

#endif

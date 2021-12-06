/******************************************************************************
 ** FUNCTION:
 **	 	This file has structure definitions and functions prototype when 
 **     UA toolkit is used in tunnelled mode.
 ******************************************************************************
 **
 ** FILENAME		: sdf_tunnelled_media.h
 **
 ** DESCRIPTION		: This file has structure definitions and functions 
 **					  prototype when UA toolkit is used in tunnelled mode.
 **
 ** DATE		NAME		         REFERENCE		REASON
 ** ----		----		         ---------		------
 ** 09/02/2009	Rajiv Kumar          Rel 8.1		Initial
 **
 ******************************************************************************
 **				COPYRIGHT , Aricent, 2009
 *****************************************************************************/

#ifndef __SDF_TUNNELLED_MEDIA_H__
#define __SDF_TUNNELLED_MEDIA_H__


#define  SDF_MAXIMUM_STR_LEN            128 

/*Denotes that address type in cline of SDP is of type "IP4"*/
#define  SDF_CLINE_ADDRESS_IPV4_ADDR      0

/*Denotes that address type in cline of SDP is of type "IP6"*/  
#define  SDF_CLINE_ADDRESS_IPV6_ADDR      1

/*-----------------------------------------------------------------------------
 * 
 * typedef Name: Sdf_tunnelled_ty_u8bit
 *
 * Description: This data type represents a 1 byte unsigned integer.
 *
 *---------------------------------------------------------------------------*/
typedef 	unsigned char		Sdf_tunnelled_ty_u8bit;


/*-----------------------------------------------------------------------------
 * 
 * typedef Name: Sdf_tunnelled_ty_u16bit
 * 
 * Description: This data type represents a 2 byte unsigned integer. 
 * 
 *---------------------------------------------------------------------------*/
typedef 	unsigned short		Sdf_tunnelled_ty_u16bit;


/*-----------------------------------------------------------------------------
 * 
 * Enum Name: Sdf_tunnelled_ty_u32bit
 * 
 * Description: This data type represents a 4 byte unsigned integer. 
 * 
 *---------------------------------------------------------------------------*/
typedef 	unsigned int		Sdf_tunnelled_ty_u32bit;

/*-----------------------------------------------------------------------------
 * 
 * typedef Name: Sdf_ty_sessionAttrType
 * 
 * Description:  This enumeration is used to indicate which session attribute
 *               from SdpMessage need to be extracted by API
 *               sdf_ivk_uaGetElementFromSessionAttr.  
 * 
 *---------------------------------------------------------------------------*/
typedef enum
{
    Sdf_en_Origin=0,
    Sdf_en_Version,
    Sdf_en_Session,
    Sdf_en_Info,
    Sdf_en_Uri,
    Sdf_en_Key
} Sdf_ty_sessionAttrType;

/*-----------------------------------------------------------------------------
 * 
 * Enum Name: Sdf_ty_sessionAttrListType
 * 
 * Description:  This enumeration is used to indicate which session attribute
 *               from SdpMessage need to be extracted by following APIs 
 *               sdf_ivk_uaGetElementFromSessionAttrList or
 *               sdf_ivk_uaGetSizeOfSessionAttrList. 
 *               These attributes are maintained as list in SdpMessage.
 * 
 *---------------------------------------------------------------------------*/
typedef enum
{
  Sdf_en_Email=0,
  Sdf_en_Phone,
  Sdf_en_Time,
  Sdf_en_Bandwidth,
  Sdf_en_Attribute
} Sdf_ty_sessionAttrListType;

/*-----------------------------------------------------------------------------
 *
 * Structure Name: Sdf_st_string
 *
 * Description: This data type represents a structure, which consists of a 
 *              character array of specified length
 *
 *---------------------------------------------------------------------------*/
typedef struct
{
    /* Specifies the length of the string including '\0' character */ 
    Sdf_tunnelled_ty_u16bit dStrLen;
    
    /* Array of characters */ 
    Sdf_tunnelled_ty_u8bit dStr[SDF_MAXIMUM_STR_LEN];  
    
}Sdf_st_string;

/*-----------------------------------------------------------------------------
*
* NAME : Sdf_st_address
*
* DESCRIPTION  : This data type is used to define a structure, which can
*                specifies the address type and connection address
*                (c line in SDP) received or needed to be send in SDP message.
*
-----------------------------------------------------------------------------*/
typedef struct
{
    /* Specifies the type of the format for the connection address
       (c line in SDP) present in the dAddrVal parameter*/
    Sdf_tunnelled_ty_u8bit        dAddrType;    

    /* Specifies the string buffer containing the connection address
       in a string format defined by the dAddrType field.*/
    Sdf_st_string                 dAddrVal; 
    
}Sdf_st_address;

/*-----------------------------------------------------------------------------
*
* NAME : Sdf_st_cLineInSdp
*
* DESCRIPTION  : This data type is used by UA toolkit for getting and setting
*                the c line in SDP.This structure populate all the information
*                received in c line of SDP as individual element.
*
-----------------------------------------------------------------------------*/
typedef struct
{
    /*Contains the network type as present in c line of SDP.*/
    Sdf_st_string        dNetType; 
      
    /*Contains the IP Address present in C line of SDP*/
    Sdf_st_address       dNetworkAddress;
} Sdf_st_cLineInSdp;

/*-----------------------------------------------------------------------------
*
* NAME : Sdf_st_mLineInSdp
*
* DESCRIPTION  : This data type is used by UA toolkit for getting and setting
*                the m line in SDP.This structure populate all the information
*                received in m line of SDP as individual element.
*
-----------------------------------------------------------------------------*/
typedef struct
{
    /*Contains the media type as present in m line of SDP*/
    Sdf_st_string                 dMediaType; 
    /*Contains the Port for RTP as present in m line of SDP*/
    Sdf_tunnelled_ty_u32bit       dPort;
    /*Contains the number of port,denoting the number of RTP sessions*/
    Sdf_tunnelled_ty_u16bit       dNumOfPorts;
    /*Contains the Protocol as present in m line of SDP*/
    Sdf_st_string                 dProtocol;
    /*Contains the format as present in m line of SDP*/
    Sdf_st_string                 dFormat;
} Sdf_st_mLineInSdp;

#endif


#ifndef _ZYUTIL_SFP_H
#define _ZYUTIL_SFP_H

#define DDMI_STRING_MAX_LENGTH	16
typedef struct sfp_ddmi_state
{
   int present;		// 1 means sfp pluged, other is 0.
   float rx_power;	// unit as dBm, the valid value is -40~+8.2, set -41 means power = 0
   float tx_power;	// unit as dBm, the valid value is -40~+8.2, set -41 means power = 0
   float temperature;	// unit as C.
   unsigned char sfp_vendor[DDMI_STRING_MAX_LENGTH];	// Vendor name, end with 0x20
   unsigned char sfp_pn[DDMI_STRING_MAX_LENGTH];		// Vendor part number, end with 0x20
   unsigned char sfp_sn[DDMI_STRING_MAX_LENGTH];		// Vendor serial number, end with 0x20
}sfp_ddmi_state_t;



/*!
 *  Open first i2c bus, /dev/i2c-0
 *
 *  @return     -1 when open fail
 *              fd, file description for /dev/i2c-0
 */
int zyUtil_i2c_open();

/*!
 *  close the i2c bus,
 *
 *  @return     0 when succeed
 *
 */
int zyUtil_i2c_close(int fd);

/*!
 *  Assign Slave Address for i2c bus
 *
 *  @return     0 is succeed, otherwise means fail.
 *
 */
int zyUtil_i2c_setSlaveAddress(int fd, int slave_address);

/*!
 *  Get the value from offset [reg] with length [bufsize] for dedicate i2c device
 *
 *  @return     read out length.
 *
 */
int zyUtil_i2c_read_register(int fd, unsigned char reg, unsigned char *buf, int bufsize);

/*!
 *  Check if the SFP module is present or not.
 *
 *  @return     1 means present, 0 means not, -1 means access fail.
 *
 */
int zyUtil_is_sfp_present(void);

/*!
 *  Check if the BOSA alread register the i2c device.
 *
 *  @return     1 means i2c device alread registered, 0 means not, -1 means access fail.
 *
 */
int zyUtil_bosa_exist(void);

/*!
 *  Display DDMI state to console.
 *
 *  @return     0 if succeed
 *
 */
int dump_DDMI_state(sfp_ddmi_state_t *ddmi_state);
/*!
 *  Read out the DDMI statue from SFP module.
 *
 *  @return     0 if succeed, otherwise means fail.
 *
 */
int zyUtil_sfp_read_ddmi_state(sfp_ddmi_state_t *ddmi_state);

/*!
 *  Check mii if the SFP module is link up or not.
 *
 *  @return     1 means up, 0 means down, -1 means access fail.
 *
 */
int zyUtil_is_sfp_linkup(void);

 
#ifdef BROADCOM_PLATFORM
  /*!
  *  ioctl get SFP speed/duplex.
  *
  *  @return	 0 if succeed
  *
  */
int zyUtil_netdevice_sfp_info(char* ifname, int* intIfBitRate, int* intIfDuplex);

#endif

#endif

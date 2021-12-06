#!/bin/sh
PROFILE_CFG=/userfs/profile.cfg
if [ -f $PROFILE_CFG ] ; then
    . $PROFILE_CFG
fi

#============================================================================================#
# To check RT30xxEEPROM.bin and CALDATA_default.bin data are valid or not on flash and /etc/
#============================================================================================#
echo "To check RT30xxEEPROM.bin and CALDATA_default.bin data"

EEPROM_RA_OFFSET=-1
EEPROM_RA_AC_OFFSET=-1
MAX_EEPROM_BIN_FILE_SIZE=0
CALDATA_RA_OFFSET=-1
CALDATA_RA_AC_OFFSET=-1
MAX_CALDATA_BIN_FILE_SIZE=0

E2P_24G_PATH="/etc/RT30xxEEPROM.bin"
E2P_5G_PATH="/etc/Wireless/RT2860AP_AC/RT30xxEEPROM.bin"
PreK_24G_PATH="/etc/CALDATA_default.bin"
PreK_5G_PATH="/etc/Wireless/RT2860AP_AC/CALDATA_default.bin"
OFE2P_24G_PATH="/tmp/E2P_24G_Onflash.bin"
OFE2P_5G_PATH="/tmp/E2P_5G_Onflash.bin"
OFPreK_24G_PATH="/tmp/PreK_24G_Onflash.bin"
OFPreK_5G_PATH="/tmp/PreK_5G_Onflash.bin"

if [ "$TCSUPPORT_RESERVEAREA_BLOCK" = "4" ] ;then
	EEPROM_RA_OFFSET=393216
	EEPROM_RA_AC_OFFSET=393728
	MAX_EEPROM_BIN_FILE_SIZE=512
fi

if [ "$TCSUPPORT_RESERVEAREA_BLOCK" = "6" ] ;then
	EEPROM_RA_OFFSET=0
	EEPROM_RA_AC_OFFSET=131072
	MAX_EEPROM_BIN_FILE_SIZE=1024
	CALDATA_RA_OFFSET=4096
	CALDATA_RA_AC_OFFSET=135168
	MAX_CALDATA_BIN_FILE_SIZE=36864
fi

if [ $MAX_EEPROM_BIN_FILE_SIZE != 0 ] ;then
	if [  "$TCSUPPORT_WLAN_MT7615_11N" != "" ] || [ "$TCSUPPORT_WLAN_MT7615D" != "" ] ;then
		if [ $EEPROM_RA_OFFSET != -1 ] ;then
			if [ -f $E2P_24G_PATH ] ;then
				echo "Check MT7615E 2.4G $E2P_24G_PATH valid or not"
				E2PChk=`hexdump -n 2 -e '/2 "%02X\n"' $E2P_24G_PATH`
				if [ "$E2PChk" == "1576" ] ;then
					echo "MT7615E 2.4G $E2P_24G_PATH is valid data!"
				else
					echo -e "\033[41;37m### Using default MT7615E 2.4G EEPROM data ###\033[0m"
					cp -rf /usr/etc/Wireless/MFG/RT30xxEEPROM_24G.bin $E2P_24G_PATH
				fi
			else
				echo "Reading MT7615E 2.4G EEPROM from flash reservearea and check valid or not"
				mtd readflash $OFE2P_24G_PATH $MAX_EEPROM_BIN_FILE_SIZE $EEPROM_RA_OFFSET reservearea
				echo "Checking MT7615E 2.4G EEPROM..."
				E2PChk=`hexdump -n 2 -e '/2 "%02X\n"' $OFE2P_24G_PATH`
				if [ "$E2PChk" == "1576" ] ;then
					echo "Valid data!"
					cat $OFE2P_24G_PATH > $E2P_24G_PATH
				else
					echo -e "\033[41;37m### Using default MT7615E 2.4G EEPROM data ###\033[0m"
					cp -rf /usr/etc/Wireless/MFG/RT30xxEEPROM_24G.bin $E2P_24G_PATH
				fi			
				rm $OFE2P_24G_PATH
			fi
		fi
	fi
	if [ "$TCSUPPORT_DUAL_WLAN_MT7615E" != "" ] || [ "$TCSUPPORT_WLAN_MT7615D" != "" ] ;then
		if [ $EEPROM_RA_AC_OFFSET != -1 ] ;then
			if [ -f $E2P_5G_PATH ] ;then
				echo "Check MT7615E 5G $E2P_5G_PATH valid or not"
				E2PChk=`hexdump -n 2 -e '/2 "%02X\n"' $E2P_5G_PATH`
				if [ "$E2PChk" == "1576" ] ;then
					echo "MT7615E 5G $E2P_5G_PATH is valid data!"
				else
					echo -e "\033[41;37m### Using default MT7615E 5G EEPROM data ###\033[0m"
					cp -rf /usr/etc/Wireless/MFG/RT30xxEEPROM_5G.bin $E2P_5G_PATH
				fi
			else
				echo "Reading MT7615E 5G EEPROM from flash reservearea and check valid or not"
				mtd readflash $OFE2P_5G_PATH $MAX_EEPROM_BIN_FILE_SIZE $EEPROM_RA_AC_OFFSET reservearea
				echo "Checking MT7615E 5G EEPROM..."
				E2PChk=`hexdump -n 2 -e '/2 "%02X\n"' $OFE2P_5G_PATH`
				if [ "$E2PChk" == "1576" ] ;then
					echo "Valid data!"
					cat $OFE2P_5G_PATH > $E2P_5G_PATH
				else
					echo -e "\033[41;37m### Using default MT7615E 5G EEPROM data ###\033[0m"
					cp -rf /usr/etc/Wireless/MFG/RT30xxEEPROM_5G.bin $E2P_5G_PATH
				fi			
				rm $OFE2P_5G_PATH
			fi		
		fi
	fi
fi

#*******************Pre-K*******************
if [ $MAX_CALDATA_BIN_FILE_SIZE != 0 ] ;then
	if [  "$TCSUPPORT_WLAN_MT7615_11N" != "" ] || [ "$TCSUPPORT_WLAN_MT7615D" != "" ] ;then
		if [ $CALDATA_RA_OFFSET != -1 ] ;then
			if [ -f $PreK_24G_PATH ] ;then
				echo "Check MT7615E 2.4G $PreK_24G_PATH valid or not"
				E2PChk=`hexdump -n 2 -e '/2 "%02X\n"' $PreK_24G_PATH`
				if [ "$E2PChk" != "FFFF" ] ;then
					echo "MT7615E 2.4G $PreK_24G_PATH is valid data!"
				else
					echo -e "\033[41;37m### Using default 2.4G CALDATA ###\033[0m"
					cp -rf /usr/etc/Wireless/MFG/CALDATA_24G_default.bin $PreK_24G_PATH
				fi
			else
				echo "Reading MT7615E 2.4G CALDATA from flash reservearea and check valid or not"
				mtd readflash $OFPreK_24G_PATH $MAX_CALDATA_BIN_FILE_SIZE $CALDATA_RA_OFFSET reservearea
				echo "Checking MT7615E 2.4G CALDATA..."
				E2PChk=`hexdump -n 2 -e '/2 "%02X\n"' $OFPreK_24G_PATH`
				if [ "$E2PChk" != "FFFF" ] ;then
					echo "Valid data!"
					cat $OFPreK_24G_PATH > $PreK_24G_PATH
				else
					echo -e "\033[41;37m### Using default 2.4G CALDATA ###\033[0m"
					cp -rf /usr/etc/Wireless/MFG/CALDATA_24G_default.bin $PreK_24G_PATH
				fi
				rm $OFPreK_24G_PATH
			fi
		fi
	fi
	if [ "$TCSUPPORT_DUAL_WLAN_MT7615E" != "" ] || [ "$TCSUPPORT_WLAN_MT7615D" != "" ] ;then
		if [ $CALDATA_RA_AC_OFFSET != -1 ] ;then
			if [ -f $PreK_5G_PATH ] ;then
				echo "Check MT7615E 5G $PreK_5G_PATH valid or not"
				E2PChk=`hexdump -n 2 -e '/2 "%02X\n"' $PreK_5G_PATH`
				if [ "$E2PChk" != "FFFF" ] ;then
					echo "MT7615E 5G $PreK_5G_PATH is valid data!"
				else
					echo -e "\033[41;37m### Using default 5G CALDATA ###\033[0m"
					cp -rf /usr/etc/Wireless/MFG/CALDATA_5G_default.bin $PreK_5G_PATH
				fi
			else
				echo "Reading MT7615E 5G CALDATA from flash reservearea and check valid or not"
				mtd readflash $OFPreK_5G_PATH $MAX_CALDATA_BIN_FILE_SIZE $CALDATA_RA_AC_OFFSET reservearea
				echo "Checking MT7615E 5G CALDATA..."
				E2PChk=`hexdump -n 2 -e '/2 "%02X\n"' $OFPreK_5G_PATH`
				if [ "$E2PChk" != "FFFF" ] ;then
					echo "Valid data!"
					cat $OFPreK_5G_PATH > $PreK_5G_PATH
				else
					echo -e "\033[41;37m### Using default 5G CALDATA ###\033[0m"
					cp -rf /usr/etc/Wireless/MFG/CALDATA_5G_default.bin $PreK_5G_PATH
				fi
				rm $OFPreK_5G_PATH
			fi
		fi
	fi
fi


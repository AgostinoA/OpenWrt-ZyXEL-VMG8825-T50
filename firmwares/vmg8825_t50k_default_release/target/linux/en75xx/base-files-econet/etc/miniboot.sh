#!/bin/sh
PROFILE_CFG=/userfs/profile.cfg
if [ -f $PROFILE_CFG ] ; then
    . $PROFILE_CFG
fi
echo "Start run miniboot.sh"
############ Required jobs of mini boot ###############
####### Set LAN IP
TE_LAN_IP=192.192.192.4
ifconfig br0 $TE_LAN_IP netamsk 255.255.255.0 up
####### Set TE login account
# echo admin:\$1\$\$r.VXYDys3wCcPiuJQEH4d/:0:0:root:/:/bin/sh > /etc/usertty
# echo admin:\$1\$\$r.VXYDys3wCcPiuJQEH4d/:0:0:root:/:/bin/sh > /etc/passwd
####### Mount original root filesystem on flash for fwcheck (dual image)
#BOOT_SELECT=`sys getbs`
mkdir /var/mnt
if [ "$BOOT_SELECT" != "slave" ]; then
ROOTFS=mtdblock3
else
ROOTFS=mtdblock6
fi
mount -t squashfs -o ro /dev/$ROOTFS /var/mnt/ &
sleep 1

# ln -s /var/mnt/usr/sbin/topaz-linux.lzma.img /usr/sbin/topaz-linux.lzma.img
# ln -s /var/mnt/usr/sbin/u-boot.bin /usr/sbin/u-boot.bin

# echo "&&&&&&&&&&&&&&&&&&&&&&&&&&&&& Enable RGMII1 for QTN &&&&&&&&&&&&&&&&&&&&&&&&&&&&& "
# echo "active 23 0" > /proc/tc3162/gpio_output
# sleep 1
# echo "active 23 1" > /proc/tc3162/gpio_output

####### Check if calibration data needs to load from flash or not
# sys rdclbfromflash
####### Set WLAN 2.4G config
#/etc/Wireless/RT2860AP/enableEfuseBufferMode.sh
IWPRIV_PATH="/usr/sbin/iwpriv"
$IWPRIV_PATH ra0 set CountryRegion=0
$IWPRIV_PATH ra0 set BeaconPeriod=100
$IWPRIV_PATH ra0 set RTSThreshold=2347
$IWPRIV_PATH ra0 set FragThreshold=2346
$IWPRIV_PATH ra0 set DtimPeriod=1
$IWPRIV_PATH ra0 set TxPower=100
$IWPRIV_PATH ra0 set session_timeout_interval=1800
$IWPRIV_PATH ra0 set IdleTimeout=3600
$IWPRIV_PATH ra0 set own_ip_addr=$TE_LAN_IP
$IWPRIV_PATH ra0 set IgmpSnEnable=1
$IWPRIV_PATH ra0 set ACSCheckTime=900
$IWPRIV_PATH ra0 set WirelessMode=9
$IWPRIV_PATH ra0 set BasicRate=15
$IWPRIV_PATH ra0 set HtBw=1
$IWPRIV_PATH ra0 set HtBssCoex=0
$IWPRIV_PATH ra0 set AutoChannelSel=0
$IWPRIV_PATH ra0 set Channel=6
$IWPRIV_PATH ra0 set HtGi=1
$IWPRIV_PATH ra0 set HtMcs=33
$IWPRIV_PATH ra0 set HideSSID=0
$IWPRIV_PATH ra0 set AuthMode=OPEN
$IWPRIV_PATH ra0 set EncrypType=NONE
$IWPRIV_PATH ra0 set SSID="MFG"
$IWPRIV_PATH ra0 set RekeyInterval=1800
$IWPRIV_PATH ra0 set DefaultKeyID=2
$IWPRIV_PATH ra0 set AccessPolicy=0
$IWPRIV_PATH ra0 set ACLClearAll=1
$IWPRIV_PATH ra0 set WscConfStatus=2
$IWPRIV_PATH ra0 set WscSetupLock=0
$IWPRIV_PATH ra0 set WscMaxPinAttack=10
$IWPRIV_PATH ra0 set WscSetupLockTime=0
$IWPRIV_PATH ra0 set WscSetupPinAttackCheckTime=5
$IWPRIV_PATH ra0 set WscConfMode=7
$IWPRIV_PATH ra0 set NoForwarding=0
$IWPRIV_PATH ra0 set NoForwardingBTNBSSID=0

$IWPRIV_PATH rai0 set AuthMode=OPEN
$IWPRIV_PATH rai0 set EncrypType=NONE
$IWPRIV_PATH rai0 set IEEE8021X=0
$IWPRIV_PATH rai0 set own_ip_addr=$TE_LAN_IP
$IWPRIV_PATH rai0 set HT_BSSCoexistence=0
$IWPRIV_PATH rai0 set SSID=MFG_5G



####### Enable telnet
if [ "$TELEFONICA_SPAIN_TELNET_NAME" != "" ] ;then
/etc/$TELEFONICA_SPAIN_TELNET_NAME -l /bin/login -d -p 23 &
else
/usr/sbin/telnetd -p 23
fi
####### Bring up 5G
#if [ "$MSTC_WLAN_5G" != "" ]; then
#/etc/extra_func_mini.sh
#fi

rm -rf /usr/etc/rc3.d/S46crond
rm -rf /usr/etc/rc3.d/S46syslog-ng
rm -rf /usr/etc/rc3.d/S48dnsmasq

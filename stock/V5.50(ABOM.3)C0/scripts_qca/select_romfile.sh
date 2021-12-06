#!/bin/sh

if [[ "$1" != "" ]] ; then
	R=$1
	echo "Change to using $R config!"
else
	echo "No need to change default config!"
#	exit 0
fi
SELECT_ZCFG=`cat .config | grep "CONFIG_PACKAGE_zcfg=" | cut -d'=' -f2`
if [ "$SELECT_ZCFG" = "y" ]; then
	echo "zcfg was enabled!"
	grep CONFIG_ZCFG_DEFAULT_ROMFILE $TOPDIR/.config | sed -i s/CONFIG_ZCFG_DEFAULT_ROMFILE.*/CONFIG_ZCFG_DEFAULT_ROMFILE=\"$1\"/g $TOPDIR/.config
else
	echo "zcfg was disable!"
fi

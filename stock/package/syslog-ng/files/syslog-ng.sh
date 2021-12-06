#!/bin/sh

export PATH=/home/bin:/home/scripts:/opt/bin:/bin:/sbin:/usr/bin:/usr/sbin
#export LD_LIBRARY_PATH=/lib/public:/lib/private:/usr/lib:/lib

SUPPORT_LIB64=`ls / | grep lib64`
if [ "$SUPPORT_LIB64" == "lib64" ] ;then
export LD_LIBRARY_PATH=/lib/public:/lib/private:/usr/lib:/lib:/lib64/gpl:/lib64
else
export LD_LIBRARY_PATH=/lib/public:/lib/private:/usr/lib:/lib
fi

case "$1" in
	start)
		ln -s /var/log/log /dev/log
		cp /etc/syslog-ng/syslog-ng_init.conf /var/syslog-ng.conf
		#/usr/sbin/syslog-ng -f /var/syslog-ng.conf
		exit 0
		;;

	*)
		echo "$0: unrecognized option $1"
		exit 1
		;;

esac


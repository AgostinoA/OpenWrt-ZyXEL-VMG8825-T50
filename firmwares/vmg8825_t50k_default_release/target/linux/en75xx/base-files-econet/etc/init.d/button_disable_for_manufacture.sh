#!/bin/sh

ifconfig br0 | grep "inet addr" | awk -F":" '{print $2}' | sed "s/\ Bcast//g" > /tmp/br0_ipaddr

BR0_IPADDRESS=`cat /tmp/br0_ipaddr`
# echo "BR0_IPADDRESS = $BR0_IPADDRESS"
rm -rf /tmp/br0_ipaddr

if [ $BR0_IPADDRESS == "192.192.192.4" ]; then
	echo "To setting button into test mode !"
	sys btntest 1
	/etc/init.d/disable_lan.sh start &
fi

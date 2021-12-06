#!/bin/sh

#nat basic modules
insmod /lib/modules/`uname -r`/nf_conntrack.ko
insmod /lib/modules/`uname -r`/nf_defrag_ipv4.ko
insmod /lib/modules/`uname -r`/nf_conntrack_ipv4.ko
insmod /lib/modules/`uname -r`/nf_nat.ko
if grep -q '4.1' /proc/version && echo $?; then
insmod /lib/modules/`uname -r`/nf_nat_ipv4.ko
insmod /lib/modules/`uname -r`/nf_nat_masquerade_ipv4.ko
fi

#iptables basic modules
insmod /lib/modules/`uname -r`/ip_tables.ko
insmod /lib/modules/`uname -r`/iptable_nat.ko
insmod /lib/modules/`uname -r`/iptable_filter.ko
insmod /lib/modules/`uname -r`/iptable_mangle.ko
insmod /lib/modules/`uname -r`/ipt_MASQUERADE.ko

#!/bin/sh
mknod /dev/fuse c 10 229
mkdir /dev/misc
mknod /dev/misc/fuse c 10 229

mkdir -p /dev/usb
mkdir -p /dev/shm
# TCSUPPORT_RA_HWNAT
mknod /dev/hwnat0 c 220 0
mknod /dev/acl0 c 230 0
mknod /dev/ac0 c 240 0
mknod /dev/mtr0 c 250 0

mknod /dev/gpio c 10 123
mknod /dev/led c 10 151
# TCSUPPORT_PORTBIND
mknod /dev/pmap c 200 0
mknod /dev/ppp c 108 0
mknod /dev/ptmx c 5 2
mknod /dev/ptyp0 c 2 0
mknod /dev/ptyp1 c 2 1
mknod /dev/ptyp2 c 2 2
# TCSUPPORT_QOS
mknod /dev/qostype c 111 2
# TCSUPPORT_CT_DS_LIMIT
mknod /dev/qos_dslimit c 112 0
mknod /dev/vdsp c 232 0
mknod /dev/slic c 231 0
mknod /dev/spi c 233 0
mknod /dev/ttyp0 c 3 0
mknod /dev/ttyp1 c 3 1
mknod /dev/ttyp2 c 3 2
mknod /dev/watchdog c 10 130
# TCSUPPORT_MUH_TEST
mknod /dev/cli c 234 0
# TCSUPPORT_USB_3G_DONGLE
mknod /dev/ttyUSB0 c 188 0
mknod /dev/ttyUSB1 c 188 1
mknod /dev/ttyUSB2 c 188 2
mknod /dev/ttyUSB3 c 188 3
mknod /dev/ttyUSB4 c 188 4
# TCSUPPORT_UART2
mknod /dev/ttyS20 c 4 65
# TCSUPPORT_CPU_EN7516
mknod /dev/ttyS30 c 4 66
# TCSUPPORT_CPU_EN7580
#mknod /dev/ttyS30 c 4 66
mknod /dev/ttyS40 c 4 67
mknod /dev/ttyS50 c 4 68
# TCSUPPORT_FON
mknod /dev/tun c 10 200

mknod /dev/mtd b 31 0
# TCSUPPORT_PON_VLAN
mknod /dev/ponvlan c 215 0
# TCSUPPORT_PON_MAC_FILTER
mknod /dev/ponmacfilter c 216 0
# TCSUPPORT_PONMGR
mknod /dev/pon c 190 0
# TCSUPPORT_WAN_PTM
mknod /dev/ptm c 191 0
# TCSUPPORT_WAN_EPON
mknod /dev/epon_mac c 221 0
# TCSUPPORT_GPON_MAPPING, TCSUPPORT_EPON_MAPPING
mknod /dev/xponmap c 210 0
# TCSUPPORT_DRIVER_API, TCSUPPORT_XPON_HAL_API_EXT
mknod /dev/fe c 226 0
# TCSUPPORT_DRIVER_API
mknod /dev/atm c 113 0
# TCSUPPORT_WLAN
mknod /dev/pcie c 225 0
# TCSUPPORT_QDMA_BUFMGR
mknod /dev/qdma_lan c 119 0
mknod /dev/qdma_wan c 120 0
# TCSUPPORT_FWC_MCST
mknod /dev/ecnt_igmp c 253 0
# TCSUPPORT_FWC_TRAFFIC_CLASSIFY, TCSUPPORT_CMCCV2
mknod /dev/traffic_classify c 236 0
# TCSUPPORT_FWC_ENV
mknod /dev/personality_parm c 237 0
# TCSUPPORT_VOIP
#mknod /dev/AclDsp c 234 0
#mknod /dev/FxsDrv c 235 0
# TCSUPPORT_RA_HWNAT
mknod /dev/hwnat0 c 220 0
mknod /dev/acl0 c 230 0
mknod /dev/ac0 c 240 0
mknod /dev/mtr0 c 250 0
# TCSUPPORT_XPON_HAL_API_EXT
mknod /dev/vlanfilter c 238 0
# TCSUPPORT_MIPS_1004K
mknod /dev/cpu_interrupt c 224 0

ln -s /var/log/log dev/log

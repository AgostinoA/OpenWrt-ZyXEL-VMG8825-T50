#!/bin/sh

DRIVER_PATH=/lib/modules/`uname -r`
# don't change order
COMMON_DRIVERS="module_sel.ko tcsmux.ko tcportbind.ko tcvlantag.ko tcledctrl.ko tccicmd.ko sif"
LAN_DRIVERS="raeth.ko qdma.ko"

for i in $COMMON_DRIVERS $LAN_DRIVERS; do
        lsmod | grep ${i%.*} &>/dev/null || insmod $DRIVER_PATH/$i
done

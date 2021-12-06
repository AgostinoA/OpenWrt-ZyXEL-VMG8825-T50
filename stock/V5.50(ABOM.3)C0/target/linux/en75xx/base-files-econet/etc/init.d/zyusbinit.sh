#!/bin/sh
echo -e "\033[1;34mInitial USB driver...\033[0m"
KERNELVER=`uname -r`
test -e /lib/modules/$KERNELVER/scsi_mod.ko && insmod /lib/modules/$KERNELVER/scsi_mod.ko
test -e /lib/modules/$KERNELVER/scsi_wait_scan.ko && insmod /lib/modules/$KERNELVER/scsi_wait_scan.ko
test -e /lib/modules/$KERNELVER/sd_mod.ko && insmod /lib/modules/$KERNELVER/sd_mod.ko
test -e /lib/modules/$KERNELVER/nls_base.ko && insmod /lib/modules/$KERNELVER/nls_base.ko
test -e /lib/modules/$KERNELVER/nls_utf8.ko && insmod /lib/modules/$KERNELVER/nls_utf8.ko
test -e /lib/modules/$KERNELVER/nls_cp936.ko && insmod /lib/modules/$KERNELVER/nls_cp936.ko
test -e /lib/modules/$KERNELVER/fat.ko && insmod /lib/modules/$KERNELVER/fat.ko
test -e /lib/modules/$KERNELVER/vfat.ko && insmod /lib/modules/$KERNELVER/vfat.ko
test -e /lib/modules/$KERNELVER/exfat.ko && insmod /lib/modules/$KERNELVER/exfat.ko
test -e /lib/modules/$KERNELVER/hfs.ko && insmod /lib/modules/$KERNELVER/hfs.ko
test -e /lib/modules/$KERNELVER/hfsplus.ko && insmod /lib/modules/$KERNELVER/hfsplus.ko
test -e /lib/modules/$KERNELVER/usbcore.ko && insmod /lib/modules/$KERNELVER/usbcore.ko
test -e /lib/modules/$KERNELVER/usblp.ko && insmod /lib/modules/$KERNELVER/usblp.ko
test -e /lib/modules/$KERNELVER/usb-storage.ko && insmod /lib/modules/$KERNELVER/usb-storage.ko
if [ "$1" != "usb30disable" ]; then
    if [ -z "$1" ]; then
        test -e /lib/modules/$KERNELVER/xhci-hcd.ko && insmod /lib/modules/$KERNELVER/xhci-hcd.ko
    else
        test -e /lib/modules/$KERNELVER/xhci-hcd.ko && insmod /lib/modules/$KERNELVER/xhci-hcd.ko USB3_Enable=1
    fi
else
    test -e /lib/modules/$KERNELVER/xhci-hcd.ko && insmod /lib/modules/$KERNELVER/xhci-hcd.ko USB3_Enable=0
fi
test -e /lib/modules/$KERNELVER/xhci-plat-hcd.ko && insmod /lib/modules/$KERNELVER/xhci-plat-hcd.ko

#EJECT need
test -e /lib/modules/$KERNELVER/cdrom.ko && insmod /lib/modules/$KERNELVER/cdrom.ko
test -e /lib/modules/$KERNELVER/isofs.ko && insmod /lib/modules/$KERNELVER/isofs.ko
test -e /lib/modules/$KERNELVER/sr_mod.ko && insmod /lib/modules/$KERNELVER/sr_mod.ko

if [ "$KERNELVER" = "3.18.21" ];then
	mount --bind /dev/bus /proc/bus
	ln -s /sys/kernel/debug/usb/devices /proc/bus/usb/devices
else
	mount -t usbfs usbfs /proc/bus/usb/
fi
#!/bin/bash
MYDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $MYDIR
export QEMU_AUDIO_DRV="none"
qemu-system-arm -M        vexpress-a9                                               \
                -cpu      cortex-a9                                                      \
                -m        512                                                           \
                -nographic                                                               \
                -kernel   $MYDIR/zImage                                               \
                -drive    file=$MYDIR/rootfs.ext2,index=0,media=disk,format=raw,if=sd \
                -dtb      $MYDIR/vexpress-v2p-ca9.dtb                                 \
                -net      nic                                                         \
                -net      user,hostfwd=tcp::2222-:22             \
                -append   "rw console=ttyAMA0 console=tty root=/dev/mmcblk0"

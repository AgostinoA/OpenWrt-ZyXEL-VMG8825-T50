#!/bin/sh
mknod /dev/fuse c 10 229
mkdir /dev/misc
mknod /dev/misc/fuse c 10 229

mkdir -p /dev/usb
mkdir -p /dev/shm

mknod /dev/hwnat0 c 220 0
mknod /dev/acl0 c 230 0
mknod /dev/ac0 c 240 0
mknod /dev/mtr0 c 250 0
mknod /dev/gpio c 10 123
mknod /dev/led c 10 151

mknod /dev/pmap c 200 0
mknod /dev/ppp c 108 0
mknod /dev/ptmx c 5 2
mknod /dev/ptyp0 c 2 0
mknod /dev/ptyp1 c 2 1
mknod /dev/ptyp2 c 2 2
mknod /dev/qostype c 111 2
mknod /dev/vdsp c 245 0
mknod /dev/slic c 251 0
mknod /dev/ttyp0 c 3 0
mknod /dev/ttyp1 c 3 1
mknod /dev/ttyp2 c 3 2
mknod /dev/watchdog c 10 130

mknod /dev/ttyUSB0 c 188 0
mknod /dev/ttyUSB1 c 188 1
mknod /dev/ttyUSB2 c 188 2
mknod /dev/ttyUSB3 c 188 3
mknod /dev/ttyUSB4 c 188 4



#!/bin/sh

# convert character to ASCII value
ascii() {
	echo $(printf "%d" "'$1")
}

# convert ASCII value to character
char () {
	[ "$1" -lt 256 ] || return
	printf "\\$(printf '%03o' "$1")"
}

# Create character device
# cdev <dev_name> <major> <minor>
cdev() {
	[ -c /dev/$1 ] || mknod /dev/$1 c $2 $3
}

# Create block device
# bdev <dev_name> <major> <minor>
bdev() {
	[ -b /dev/$1 ] || mknod /dev/$1 b $2 $3
}

# Create generic character device
cdev mem	1	1
cdev kmem	1	2
cdev null	1	3
cdev port	1	4
cdev zero	1	5
cdev random	1	8
cdev urandom	1	9
cdev tty	5	0
cdev console	5	1


# Create TTY device (/dev/tty*, /dev/ttyS*)
MAX_DEV_NO=0
i=0
while [ $i -le $MAX_DEV_NO ]; do
  cdev tty$i	4	$i
  cdev ttyS$i	4	$((i+64))
  i=$((i+1))
done


# Create MTD device (/dev/mtd*, /dev/mtd*ro, /dev/mtdblock*)
MAX_DEV_NO=13
DEV_NO_BOOTLOADER=0
i=0
while [ $i -le $MAX_DEV_NO ]; do
  cdev mtd$i 90 $((i*2))

  if [ $i -gt $DEV_NO_BOOTLOADER ]; then
	chmod 666 /dev/mtd$i
  fi
  cdev mtd${i}ro 90 $((i*2+1))
  bdev mtdblock$i 31 $i
  i=$((i+1))
done


# Create RAM disk devices (/dev/ram*)
MAX_DEV_NO=5
i=0
while [ $i -le $MAX_DEV_NO ]; do
  bdev ram$i 1 $i
  i=$((i+1))
done


# Create SCSI disk device (/dev/sda*, /dev/sdb*...)
# max. device symbol is 'p', must be lowercase
MAX_DISK_SYMBOL=c
# max. device/partition number is 15
MAX_DEV_NO=3
minor=0
i=0
while [ $i -le $(($(ascii $MAX_DISK_SYMBOL)-$(ascii 'a'))) ]; do
#for i in `eval echo "{a..$MAX_DISK_SYMBOL}"`; do
  j=1
  bdev sd$(char $((i+$(ascii 'a')))) 8 $((minor*16))
#  for j in `eval echo "{1..$MAX_DEV_NO}"`; do
  while [ $j -le $MAX_DEV_NO ]; do
    bdev sd$(char $((i+$(ascii 'a'))))$j 8 $((minor*16+j))
    j=$((j+1))
  done
  minor=$((minor+1))
  i=$((i+1))
done

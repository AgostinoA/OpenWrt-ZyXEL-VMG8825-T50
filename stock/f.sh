#!/bin/sh
user=admin
passwd=zyad1234

path=`ls bin`
src_path="bin/$path/zyxel"
src_file="ras.bin"
dst_path="fw"
dst_file="ras"

if [ "$1" != "" ] ; then
	passwd=$1
fi
ftp -n 192.168.1.1 << EOF
user $user $passwd
binary
ha
put $src_path/$src_file $dst_path/$dst_file
bye
EOF


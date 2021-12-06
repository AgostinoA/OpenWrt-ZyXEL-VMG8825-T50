#!/bin/sh

help()
{
	echo "Usage imgAlignment <file> <align>"
}

if [ $# -lt 2 ]; then
	help
	exit -1
fi

if [ ! -e $1 ]; then
	echo "\"$1\" not found!\n"
	exit -2
fi

OrigFileSize=`stat -c %s $1`
if [ $(($OrigFileSize & ($2 - 1))) == 0 ]; then
	ExpectSize=$OrigFileSize
else
	ExpectSize=$((($OrigFileSize | ($2 - 1)) + 1))
fi

PaddingSize=$(($ExpectSize - $OrigFileSize))

echo "OrigFileSize=$OrigFileSize ExpectSize=$ExpectSize PadSize=$PaddingSize"

if [ $PaddingSize -gt 0 ]; then
	dd if=/dev/zero bs=$PaddingSize count=1 | tr '\000' '\377' >>$1
fi

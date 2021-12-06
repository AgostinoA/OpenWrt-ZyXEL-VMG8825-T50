#!/bin/sh

if [[ "$1" == "" ]] ; then
	echo "Please specify the project name!"
	exit 0
fi

P=$1

echo "P=$P"

if [ ! -e $TOPDIR/configs/$P/platform.defconfig ] || [ ! -e $TOPDIR/configs/$P/project.defconfig ] ; then
	echo "copy $TOPDIR/configs/$P/$P.defconfig to .config!"
	cp $TOPDIR/configs/$P/$P.defconfig $TOPDIR/.config
else
	echo "merge $TOPDIR/configs/$P/platform.defconfig and $TOPDIR/configs/$P/project.defconfig to .config!"
	cat $TOPDIR/configs/$P/platform.defconfig $TOPDIR/configs/$P/project.defconfig > $TOPDIR/.config
fi

if [[ "$P" == "ipq807x" ]] ; then
	echo "QCA PLATFORM, use right version."
	rm -rf $TOPDIR/include $TOPDIR/scripts
	cp -rf $TOPDIR/include_qca $TOPDIR/include
	cp -rf $TOPDIR/scripts_qca $TOPDIR/scripts
fi

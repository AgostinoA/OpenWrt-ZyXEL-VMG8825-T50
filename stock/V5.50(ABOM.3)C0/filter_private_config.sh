#!/bin/sh

PRIVATE_PKG_DIR=./package/private/
PRIVATE_PACKAGE_INFO=./tmp/info/
PRIVATE_CONFIG_FILE=./private_config
MAIN_CONFIG_FILE=./.config

rm -f $PRIVATE_CONFIG_FILE

for i in `find $PRIVATE_PACKAGE_INFO -name .packageinfo-private_* | xargs grep -wl "Package:"`; do
for j in `grep -w "Package:" $i | cut -c 10- | sed 's/\r//'`; do
PKG_NAME=CONFIG_PACKAGE_$j
grep "$PKG_NAME=" $MAIN_CONFIG_FILE >> $PRIVATE_CONFIG_FILE

done
done

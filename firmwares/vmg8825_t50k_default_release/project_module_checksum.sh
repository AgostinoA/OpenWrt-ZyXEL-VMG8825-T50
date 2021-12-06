#!/bin/sh
function help() {
	echo " "
	echo "Usage:	$0 [-p <input project profile>] [-i <input file name>] [-o <output file name>] [-r <report file name>]"
	echo " "
}

rm -rf md5_cmd.txt

for ((b=1 ; b<=6 ; b=b+1 ))
do
	if [[ $1 == "" ]] ; then
		break
	elif [[ $1 == "-p" ]] ; then
		shift
		PROJECT_PROFILE=$1
		printf '%s' "./module_checksum.sh" >> md5_cmd.txt
	elif [[ $1 == "-o" ]] ; then
		shift
		MD5_OUTPUT_FILE=$1
		printf ' %s %s' "-o" "$MD5_OUTPUT_FILE" >> md5_cmd.txt
	elif [[ $1 == "-i" ]] ; then
		shift
		MD5_INPUT_FILE=$1
		printf ' %s %s' "-i" "$MD5_INPUT_FILE" >> md5_cmd.txt
	elif [[ $1 == "-r" ]] ; then
		shift
		MD5_REPORT_FILE=$1
		printf ' %s %s' "-r" "$MD5_REPORT_FILE" >> md5_cmd.txt
	elif [[ $1 == "-g" ]] ; then
		printf ' %s ' "-g" >> md5_cmd.txt
	else
		help
		exit 1
	fi
	shift
done

if [[ $PROJECT_PROFILE == "" ]] ; then
	echo "Please input project profile."
exit
fi

make P=$PROJECT_PROFILE precfg
make P=$PROJECT_PROFILE defconfig
make P=$PROJECT_PROFILE tools/prepare
make P=$PROJECT_PROFILE tools/autoconf/install
make P=$PROJECT_PROFILE target/prepare
make P=$PROJECT_PROFILE package/prepare

`cat md5_cmd.txt`

rm -rf md5_cmd.txt
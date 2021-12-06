#!/bin/sh
TIME_START=`date`
EXCLUDE_FILE_LIST=".built .pc/ patches/ .patch .configured_ /ipkg- .pdf config.log .dep_files .prepared_ /opkg/ /fs.install built-in.o .lib/ .libs/"
EXCLUDE_FILE_NAME="module_checksum_exclude.txt"
if [[ -e $EXCLUDE_FILE_NAME ]] ; then
	EXCLUDE_FILE_LIST+="`cat $EXCLUDE_FILE_NAME | grep -v ^#`"
fi
MD5="md5sum"
FILE_PATH_BUILD="./build_dir/target-*/ "
FILE_PATH_PACKAGE="./package/ "
FILE_PATH_CONFIG="./configs/"
FWID_EXT="CONFIG_ZYXEL_FIRMWARE_VERSION"
FW_VERSION=`cat .config | grep $FWID_EXT | awk -F"=" '{print $2}' | sed "s/\"//g" | sed "s/(//g" | sed "s/)//g" | sed "s/\.//g"`
PROECT_PROFILE=""
MD5_INPUT_FILE=""
MD5_OUTPUT_FILE="md5sum_$FW_VERSION.txt"
MD5_OUTPUT_TEMP_FILE="md5sum_temp.txt"
MD5_REPORT_FILE="md5sum_diff_$FW_VERSION.txt"

function announcement() {
	echo " "
	echo "=================================================================================================="
	echo " From USG Glenn: It only make sure that the revise can response to the checksum, "
	echo " not make sure no bug from the same checksum "
	echo "=================================================================================================="
	echo " PeterSu: This is only for PQA reference, not intended for PQA to reduce the testing cases. "
	echo " 			PQA should do testing no matter it is the same or not."
	echo " 			RD will not guarantee anything and there is no excuse for PQA. "
	echo " 			Otherwise, RD will not provide this tool and report to PQA anymore. "
	echo "=================================================================================================="
	echo " "
}

function help() {
	echo " "
	echo "Usage:	$0 [-p <project profile>] [-i <input file name>] [-o <output file name>] [-r <report file name>] [-h]"
	echo " "
}

for ((b=1 ; b<=6 ; b=b+1 ))
do
	if [[ $1 == "" ]] ; then
		break
	elif [[ $1 == "-p" ]] ; then
		shift
		PROJECT_PROFILE=$1
	elif [[ $1 == "-o" ]] ; then
		shift
		MD5_OUTPUT_FILE=$1
	elif [[ $1 == "-i" ]] ; then
		shift
		MD5_INPUT_FILE=$1
	elif [[ $1 == "-r" ]] ; then
		shift
		MD5_REPORT_FILE=$1
	elif [[ $1 == "-g" ]] ; then
		GEN_REPORT_ONLY="yes"
	else
		help
		exit 1
	fi
	shift
done

echo "##############################################################################"
echo "TIME_START=$TIME_START"
echo "FW_VERSION=$FW_VERSION"
echo "EXCLUDE_FILE_LIST=$EXCLUDE_FILE_LIST"
echo "MD5_OUTPUT_FILE=$MD5_OUTPUT_FILE"
if [[ $MD5_INPUT_FILE != "" ]] ; then
	echo "MD5_INPUT_FILE=$MD5_INPUT_FILE"
fi
echo "MD5_REPORT_FILE=$MD5_REPORT_FILE"
echo "PROJECT_PROFILE=$PROJECT_PROFILE"

##############################################################################
if [[ $GEN_REPORT_ONLY != "yes" ]] ; then
##############################################################################


##############################################################################
# prepare files

if [[ $PROJECT_PROFILE != "" ]] ; then
	make P=$PROJECT_PROFILE precfg defconfig
	make P=$PROJECT_PROFILE tools/prepare
	make P=$PROJECT_PROFILE tools/autoconf/install
	make P=$PROJECT_PROFILE target/prepare
	make P=$PROJECT_PROFILE package/prepare
fi

##############################################################################
# all files

ALL_FILES="`find $FILE_PATH_BUILD -type f` "
ALL_FILES+="`find $FILE_PATH_PACKAGE -type f` "
ALL_FILES+="`find $FILE_PATH_CONFIG$PROJECT_PROFILE -type f` "
rm -f all_files.txt
echo "$ALL_FILES" >> all_files.txt

##############################################################################
# filter files

cp all_files.txt filter_files.txt
for filter in $EXCLUDE_FILE_LIST
do
	cat filter_files.txt | grep -Fv $filter > tmp.txt
	mv tmp.txt filter_files.txt
done

##############################################################################
# category

rm -f category.txt

# ./package/
find -P $FILE_PATH_PACKAGE -type d | sed "s/\.\/package\///g" | awk -F"/" '{print $1}' | awk ' !x[$0]++' >> category.txt

# ./build_dir/target-mips_xxxxxxx/linux-xxxxx/
find -P $FILE_PATH_BUILD -type d | grep /linux- | sed 's/\(\.\/build_dir\/\+[a-z0-9A-Z_.-]*\)//g' | sed 's/\(\/linux-[be]\+[a-z0-9A-Z_.-]*\)//g' | awk -F"/" '{print $2}' | awk ' !x[$0]++' >> category.txt

# ./build_dir/target-mips_xxxxxxx/??????/ , exclude linux-xxxx/
find -P $FILE_PATH_BUILD -type d | grep -v /linux- | sed 's/\(\.\/build_dir\/\+[a-z0-9A-Z_.-]*\)//g' | awk -F"/" '{print $2}' | awk ' !x[$0]++' >> category.txt

# ./configs/
find -P $FILE_PATH_CONFIG -type d | sed "s/\.\/configs\///g" | awk -F"/" '{print $1}' | awk ' !x[$0]++' >> category.txt

CATEGORY_LIST=`cat category.txt | grep -v '^$' | sort -r`

##############################################################################
# md5sum

rm -f $MD5_OUTPUT_FILE
announcement > $MD5_OUTPUT_TEMP_FILE
FILTER_FILES=`cat filter_files.txt`
for file in $FILTER_FILES
do
	for filter in $CATEGORY_LIST
	do
		if [[ $file == *$filter* ]] ; then
			printf '%s\t%s\n' "`$MD5 "$file"`" "$filter" >> $MD5_OUTPUT_TEMP_FILE
			break
		fi
	done
done
cat $MD5_OUTPUT_TEMP_FILE | sort -u -k2 > $MD5_OUTPUT_FILE
rm -rf $MD5_OUTPUT_TEMP_FILE

##############################################################################
fi
##############################################################################

##############################################################################
# report

if [[ $MD5_INPUT_FILE != "" ]] ; then
	rm -f $MD5_REPORT_FILE
	diff -Na $MD5_INPUT_FILE $MD5_OUTPUT_FILE > tmp.patch
	cat tmp.patch | grep "<" | awk '{print $4, $3 }' > tmp.txt
	cat tmp.patch | grep ">" | awk '{print $4, $3 }' >> tmp.txt
	cat tmp.txt | awk ' !x[$0]++' | sort -r > tmp2.txt
	announcement > $MD5_REPORT_FILE
	echo " " >> $MD5_REPORT_FILE
	CATEGORY=""
	cat tmp2.txt | while read line; do
		tmpCategory=`echo $line | awk '{print $1}'`
		tmpFile=`echo $line | awk '{print $2}'`
		if [[ $CATEGORY != $tmpCategory ]] ; then
			CATEGORY=$tmpCategory
			printf '\n\n%s\n\t\t%s\n%s\n' "***************************************" "$CATEGORY" "***************************************" >> $MD5_REPORT_FILE
		fi
		echo "$tmpFile" >> $MD5_REPORT_FILE
	done
	rm -f tmp.txt tmp2.txt tmp.patch
fi

##############################################################################
# end

TIME_END=`date`
echo " "
echo "##############################################################################"
echo "Done!"
echo "TIME_END=$TIME_END"
if [[ $MD5_INPUT_FILE != "" ]] ; then
	echo "Please copy $MD5_OUTPUT_FILE and $MD5_REPORT_FILE to PQA. "
else
	echo "Please copy $MD5_OUTPUT_FILE to PQA. "
fi
echo "##############################################################################"



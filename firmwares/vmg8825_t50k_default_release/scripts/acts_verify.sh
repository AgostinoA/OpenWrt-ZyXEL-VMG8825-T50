#!/bin/bash
build_profile=$1
commit_sha=${CI_COMMIT_SHA}
verify=$2
branch=${CI_COMMIT_REF_NAME}
branch=feature-x
#build_profile=VMG3926-B10A_Generic
#commit_sha=b12aeae6be34d94c9f41e7ea52e6cc86c4753069

echo "===build_profile = $build_profile"
echo "===commit_sha = $commit_sha"

echo "=== checking ACTS test case ==="
acts_sha=`git log -n 1 | grep ACTS_COMMIT=`
acts_sha=`echo $acts_sha | sed 's/ACTS_COMMIT=//g' | sed 's/[ \t]//g'`
acts_model=`git log -n 1 | grep ACTS_MODEL=`
acts_model=`echo $acts_model | sed 's/ACTS_MODEL=//g' | sed 's/[ \t]//g'`
acts_skip=`echo $acts_sha | grep ACTS_SKIP`

feature=`echo $branch | grep feature-`
echo "===acts_sha = $acts_sha"
echo "===acts_model = $acts_model"
echo "===feature = $feature"
echo "===verify = $verify"

#====== modify the version string
# CI_COMMIT_SHA=478509f0ae6fe0510862e84cb0fca3ce7a17f06a
DEFCONFIG=configs/$build_profile/project.defconfig
sha=`echo $CI_COMMIT_SHA | cut -b 1-8`
sequence=`date +%S`
version=`grep CONFIG_ZYXEL_FIRMWARE_VERSION= $DEFCONFIG |  sed 's/CONFIG_ZYXEL_FIRMWARE_VERSION=//' | sed 's/\"//g'`
version=`echo $version | awk -F "-" '{print $1}'`
version=`echo $version | awk -F "_" '{print $1}'`
# echo version=$version
newVER=`echo "$version-$sha-$sequence" | cut -b 1-29`
# echo newVER=$newVER
VER="CONFIG_ZYXEL_FIRMWARE_VERSION=\"$newVER\""
rm -f .project.defconfig
grep -v CONFIG_ZYXEL_FIRMWARE_VERSION $DEFCONFIG >& .project.defconfig
echo $VER >> .project.defconfig
cp .project.defconfig $DEFCONFIG
#================================

if [ -f configs/$build_profile/acts.sh ] ; then
echo "=== Execute acts.sh for ACTS test"
./configs/$build_profile/acts.sh
fi


curpath=`pwd`
rm -rf pass2it

if [ x$feature != x ] && [ $verify == 1 ] ; then
    echo "===Feature branch"
    echo "===enter opal_auto project"
    cd ../opal_auto
    
    if [ x$acts_skip != x ] ; then
        echo "SKIP ACTS script verification"
        echo "ACTS_SKIP" >& $curpath/pass2it
        cd $curpath
        exit 0
    fi

    if [ x$acts_sha == x ] ; then
        echo "ACTS_VERIFY_FAIL No ACTS commit sha"
        echo "ACTS_FAIL" >& $curpath/pass2it
        cd $curpath
        exit 0
    fi
    
    git fetch
    git checkout $acts_sha
    if [ $? != 0 ]; then
        echo "ACTS_VERIFY_FAIL"
        echo "ACTS_FAIL" >& $curpath/pass2it
        cd $curpath
        exit 0
    fi
    git diff-tree --no-commit-id --name-only -r $acts_sha >& $curpath/pass2it
    echo "ACTS_COMMIT_SHA=$acts_sha" >> $curpath/pass2it
    cat $curpath/pass2it
    echo "===exit opal_auto project"
fi

cd $curpath


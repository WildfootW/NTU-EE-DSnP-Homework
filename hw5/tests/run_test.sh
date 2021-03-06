#!/bin/bash
#   Version 
#   Author: WildfootW
#   GitHub: github.com/WildfootW
#   Copyright (C) 2018 WildfootW All rights reserved.
#

# Absolute path to this script, e.g. /home/user/Pwngdb/install.sh
SCRIPT=$(readlink -f "$0")
# Absolute path this script is in, thus /home/user/Pwngdb
SCRIPTPATH=$(dirname "$SCRIPT")

function print_usage() {
    echo "./run_test.sh <array | bst | dlist>"
}

if  [ "$#" -eq 1 ] && { [ "$1" == "array" ] || [ "$1" == "bst" ] || [ "$1" == "dlist" ] ;} ; then
    echo "adtTest.$1"
else
    print_usage
    exit 1
fi

my_adttest="../adtTest.$1"
ref_adttest="../ref/adtTest.$1"
#dofiles="do1 do2 do3 do4 do5"
dofiles="mydo1 mydo2 mydo3"

echo "" > diff_result
for dofile in `echo $dofiles | tr ' ' '\n'`; do
    eval $my_adttest -f $dofile &> "autotest_out.$dofile"
    eval $ref_adttest -f $dofile &> "autotest_out.ref.$dofile"
    echo "=================================================" >> diff_result
    echo "                    $dofile" >> diff_result
    echo "=================================================" >> diff_result
    diff "autotest_out.$dofile" "autotest_out.ref.$dofile" >> diff_result
done


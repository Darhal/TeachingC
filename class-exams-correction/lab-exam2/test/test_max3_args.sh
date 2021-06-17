#!/bin/bash

REQUIRED_FILE="./build/max3_args"

if [ ! -f ${REQUIRED_FILE} ] 
then
    echo "⚠️ Executable ${REQUIRED_FILE} not found."
    exit 1
fi

function test_max3_args () {
    if [ ! $(./build/max3_args $1 $2 $3) = "$4" ];
    then
        echo "🔴 Test of max3_args failed with arguments '$1 $2 $3'"
        exit 1
    else
        echo "✅ Test succeeded (max3_args $1 $2 $3)."
    fi
}

test_max3_args 0 1 3 "3"
test_max3_args 0 4 1 "4"
test_max3_args 5 0 1 "5"
test_max3_args -7 0 7 "7"
test_max3_args -3 -5 -7 "-3"

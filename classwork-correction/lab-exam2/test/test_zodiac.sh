#!/bin/bash

REQUIRED_FILE="./build/zodiac_main"

if [ ! -f ${REQUIRED_FILE} ] 
then
    echo "⚠️ Executable ${REQUIRED_FILE} not found."
    exit 1
fi

function test_zodiac () {
    if [ ! $(./build/zodiac_main $1) = "$2" ];
    then
        echo "🔴 Test of zodiac failed with arguments '$1'"
        exit 1
    else
        echo "✅ Test succeeded (zodiac $1)."
    fi
}

function test_zodiac_should_fail () {
    ./build/zodiac_main $1 > /dev/null
    if [ $? -eq 0 ];
    then
        echo "🔴 Test of zodiac failed with arguments '$1'"
        exit 1
    else
        echo "✅ Test succeeded (zodiac $1)."
    fi
}

test_zodiac 1/1/2012 "Capricorne"
test_zodiac 19/3/1978 "Poisson"
test_zodiac 21/7/1976 "Cancer"
test_zodiac 31/12/1999 "Capricorne"

test_zodiac_should_fail 32/1/2000
test_zodiac_should_fail 30/2/2001
test_zodiac_should_fail 4/13/2002
test_zodiac_should_fail -1/2/2003
test_zodiac_should_fail 1/2/-500
test_zodiac_should_fail 1/3/0

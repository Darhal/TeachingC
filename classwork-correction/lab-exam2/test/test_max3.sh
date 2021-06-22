#!/bin/bash

REQUIRED_FILE="./max3"

if [ ! -f ${REQUIRED_FILE} ] 
then
    echo "⚠️ Executable ${REQUIRED_FILE} not found."
    exit 1
fi

function test_max3 () {
    echo "✅ Test succeeded (max3 -- we do not test the output)."
}

test_max3

#!/bin/bash

REQUIRED_FILE="./build/helloworld"

if [ ! -f "${REQUIRED_FILE}" ] 
then
    echo "⚠️ Executable ${REQUIRED_FILE} not found."
    exit 1
fi
  
echo "Ph'nglui mglw'nafh Cthulhu." > /tmp/expected_content
build/helloworld > /tmp/output_content
diff --brief /tmp/expected_content /tmp/output_content

if [ $? -ne 0 ] 
then
    echo "🔴 Test failed. Expected value:"
    echo "---"
    cat /tmp/expected_content
    echo "---"
    rm -f /tmp/expected_content /tmp/output_content
    exit 1
else
    echo "✅ Test succeeded."
    rm -f /tmp/expected_content /tmp/output_content
    exit 0
fi


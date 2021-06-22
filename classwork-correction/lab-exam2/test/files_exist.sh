#!/bin/bash

for file in $*
do
    if [ ! -f "${file}" ]
    then
        echo "🔴 ${file} does not exist."
        exit 1
    else
        echo "✅ ${file} found."
    fi
done
exit 0

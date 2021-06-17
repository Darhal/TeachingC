#!/bin/bash

CC="clang"
#CC="/usr/local/opt/llvm/bin/clang"

#CFLAGS="-Wall"
CFLAGS="-Wall -g -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls"

# uncomment this line, if you want to detect memory leak
# and if your platform offers support for memory leak detection
export ASAN_OPTIONS="detect_leaks=0"
# export LSAN_OPTIONS="detect_leaks=1"

mkdir -p build

echo "🚧 Exercice 0 🚧"
FILE="name.txt"
test/files_exist.sh $FILE

echo "🚧 Exercice 1 🚧"
FILE="src/helloworld.c"
test/files_exist.sh $FILE
if [ $? -eq 0 ]; then
    ${CC} ${CFLAGS} src/helloworld.c -o build/helloworld
    if [ $? -eq 0 ]; then
        test/test_helloworld.sh
        if [ $? -ne 0 ]; then
            exit 1
        fi
    fi    
fi


echo "🚧 Exercice 2 🚧"
FILE="src/max3.c src/max3.h"
test/files_exist.sh $FILE
if [ $? -eq 0 ]; then
    ${CC} ${CFLAGS} -c src/max3.c -o build/max3.o
    if [ $? -ne 0 ]; then
        exit 1
    else
        echo "✅ Compilation succeeded."
    fi
fi

FILE="src/max3_stdin.c"
test/files_exist.sh $FILE
if [ $? -eq 0 ]; then
    ${CC} ${CFLAGS} build/max3.o src/max3_stdin.c -o build/max3_stdin
    if [ $? -eq 0 ]; then
        echo "✅ Compilation succeeded."
        test/test_max3_stdin.sh
        if [ $? -ne 0 ]; then
            exit 1
        fi
    fi    
fi

FILE="src/max3_args.c"
test/files_exist.sh $FILE
if [ $? -eq 0 ]; then
    ${CC} ${CFLAGS} build/max3.o src/max3_args.c -o build/max3_args
    if [ $? -eq 0 ]; then
        echo "✅ Compilation succeeded."
        test/test_max3_args.sh
        if [ $? -ne 0 ]; then
            exit 1
        fi
    fi    
fi


echo "🚧 Exercice 3 🚧"
FILE="src/zodiac.h src/zodiac.c src/zodiac_main.c"
test/files_exist.sh $FILE
if [ $? -eq 0 ]; then
    ${CC} ${CFLAGS} src/zodiac.c src/zodiac_main.c -o build/zodiac_main
    if [ $? -eq 0 ]; then
        echo "✅ Compilation succeeded."
        test/test_zodiac.sh
        if [ $? -ne 0 ]; then
            exit 1
        fi
    fi    
fi

echo "🚧 Exercice 4 🚧"

FILE="src/directory.h src/directory.c src/directory_main.c"
test/files_exist.sh $FILE
if [ $? -eq 0 ]; then
    ${CC} ${CFLAGS} src/directory.c src/directory_main.c -o build/directory_main
    if [ $? -eq 0 ]; then
        echo "✅ Compilation succeeded."
        build/directory_main
#        test/test_directory.sh
        if [ $? -ne 0 ]; then
            exit 1
        fi
    fi    
fi

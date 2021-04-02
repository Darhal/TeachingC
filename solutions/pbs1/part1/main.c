#include <stdlib.h>
#include <stdio.h>  // not used
#include <string.h> // for testing
#include <assert.h> // for testing

unsigned int len(char* str)
{
    unsigned int i = 0;
    while (*str++)
        i++;
    return i;
}

int main()
{
    assert(strlen("Hello") == len("Hello"));
    assert(strlen("") == len(""));
    assert(strlen("\0\0") == len("\0\0"));
    assert(strlen("Hello world! This is a fairly long string") == len("Hello world! This is a fairly long string"));
}
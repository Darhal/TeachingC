#include <stdio.h>
#include <stdlib.h>
#include "max3.h"

int main(int argc, char** argv)
{
    if (argc < 4)
        return -1;

    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    int c = atoi(argv[3]);
    int m = max(a, b, c);
    printf("%d", m);
}
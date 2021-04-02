#include <stdio.h>
#include <stdlib.h>

void pyramid(int h)
{
    for (int i = 0; i < h; i++){
        for (int j = 0; j < i +1; j++)
            printf("*");
        printf("\n");
    }
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        return 1;
    }

    int h = atoi(argv[1]);
    pyramid(h);
}
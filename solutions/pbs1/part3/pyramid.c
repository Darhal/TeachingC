#include <stdio.h>
#include <stdlib.h>

void pyramid(int rows)
{
   int i, space, k = 0;

    for (i = 1; i <= rows; ++i, k = 0) {
        for (space = 1; space <= rows - i; ++space) {
            printf("  ");
        }

        while (k != 2 * i - 1) {
            printf("* ");
            ++k;
        }

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
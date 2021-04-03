#include <stdio.h>
#include <stdlib.h>

void pascal(int rows)
{
    int coef = 1, space, i, j;

    for (i = 0; i < rows; i++) {
        for (space = 1; space <= rows - i; space++)
            printf("  ");
        
        for (j = 0; j <= i; j++) {
            if (j == 0 || i == 0)
                coef = 1;
            else
                coef = coef * (i - j + 1) / j;
            
            printf("%4d", coef);
        }

        printf("\n");
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        return 1;
    }

    int rows = atoi(argv[1]);
    pascal(rows);
    return 0;
}
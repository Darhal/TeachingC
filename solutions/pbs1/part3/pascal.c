#include <stdio.h>
#include <stdlib.h>

////// méthode 1 : solution mathématique
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

////// méthode 2 : en utilisant un tableau
#define MAX_BUFFER 1024

void pascal2(int n)
{
    if (n==1) {
        printf(" 1 ");
        return;
    }
    
    int scratch_buffer[MAX_BUFFER] = { 0 };
    scratch_buffer[0] = 1;
    int tmp = 0;
    printf(" 1\n");

    for (int i = 2; i < n+1; i++){
        tmp = 0;

        for (int j = 0; j < i; j++) {
            int prev = 0;

            if (j != 0) {
                prev = scratch_buffer[j - 1];
                scratch_buffer[j - 1] = tmp;
            }
        
            tmp = prev + scratch_buffer[j];
            printf(" %d ", tmp);
        }

        scratch_buffer[i - 1] = tmp;
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
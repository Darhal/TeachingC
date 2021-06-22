#include "max3.h"
#include <stdio.h>

int main()
{
    int a, b, c;
    /*printf("Enter a : ");*/ scanf("%d", &a);
    /*printf("Enter b : ");*/ scanf("%d", &b);
    /*printf("Enter c : ");*/ scanf("%d", &c);
    int m = max(a, b, c);
    printf("%d", m);
}
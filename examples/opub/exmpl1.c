#include <stdio.h>

int x = 20;

int f1() { x = x+10; return x;}
int f2() { x = x-5;  return x;}

int main()
{
  int p = f1() + f2();
  printf ("p = %d", p);
  return 0;
}

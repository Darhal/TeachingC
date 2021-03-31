#include "a.h"
#include <stdio.h>

static int a = 3;

static void prv_func()
{
	printf("Im private %d\n", a);
}

#include "zodiac.h"
#include <stdio.h>

int main(int argc, char** argv)
{
    if (argc < 2)
        return -1;
    
    const char* date = argv[1];

    if (!is_date_valid(date)) {
        puts("The date is invalid!");
        return -1;
    }

    const char* s = calc_sign(date);

    if (!s){
        puts("The date is invalid, failed to parse!");
        return -1;
    }

    puts(s);
}
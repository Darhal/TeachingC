#include "zodiac.h"
#include <string.h>
#include <stdio.h>

const char* SIGNS[] = 
{
    "Belier",
    "Taureau",
    "Gémeaux",
    "Cancer",
    "Lion",
    "Vierge",
    "Balance",
    "Scorpion",
    "Sagittaire",
    "Capricorne",
    "Verseau",
    "Poisson"
};

pair SIGN_DATES[] = 
{
    {321, 419},
    {420, 520},
    {521, 620},
    {621, 721},
    {722, 822},
    {823, 922},
    {923, 1022},
    {1023, 1121},
    {1122, 1221},
    {22, 119},
    {120, 218},
    {219, 320},
};

int is_date_valid(const char* date)
{
    const int DAYS_PER_MONTH[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int d, m, y;
    int s = sscanf(date, "%d/%d/%d", &d, &m, &y);
    
    if (s == 3)
        if (y > 0)
            if (m >= 1 && m <= 12) {
                int isLeap = y % 400 == 0 || y % 100 != 0 || y % 4 == 0;

                if (m == 2) {
                    if (isLeap) {
                        if (d >= 1 && d <= 29)
                            return 1;
                    }
                }

                if (d >= 1 && d <= DAYS_PER_MONTH[m - 1]){
                    return 1;
                }
            }
    
    return 0;
}

int parse_date(const char* date, int* day, int* month, int* year)
{
    int s = sscanf(date, "%d/%d/%d", day, month, year);
    // printf("d: %d | m: %d | y : %d\n", *day, *month, *year);
    return s == 3;
}

const char* calc_sign(const char* date)
{
    if (!is_date_valid(date))
        return NULL;
    
    int d, m, y;
    int s = parse_date(date, &d, &m, &y);
    
    if (!s)
        return NULL;

    // FIX : Buggy when it wraps arround
    if (m == 12 && d >= 22)
        m = 0;
    
    int md = m * 100 + d;
    int len = sizeof(SIGNS) / sizeof(SIGNS[0]);

    for (int i = 0; i < len; i++) {
        pair p = SIGN_DATES[i];
        
        // printf("%d - %d - %d\n", md, p.f, p.s);
        if (md >= p.f && md <= p.s){
            return SIGNS[i];
        }
    }

    return NULL;
}
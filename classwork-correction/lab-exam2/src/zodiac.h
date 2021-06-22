#pragma once

typedef struct _Pair { int f, s; } pair;

int is_date_valid(const char* date);

int parse_date(const char* date, int* day, int* month, int* year);

const char* calc_sign(const char* date);
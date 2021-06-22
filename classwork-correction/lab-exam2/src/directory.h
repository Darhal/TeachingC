#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct person_t
{
    char* nom;
    char* tel;
} person_t;

person_t* person_create(const char* nom, const char* tel);

void person_destroy(person_t* p);

void person_display(person_t* p);


int hash(char *str, int n);

typedef struct array_t
{
    person_t** arr;
    int count;
} array;

void add_arr(array* arr, person_t* p);

void destroy_arr(array* arr);

typedef struct directory_t
{
    array* tab_hash;
    int count;
} directory_t;

directory_t* directory_create(int n);

void directory_destroy(directory_t* d);

void directory_add_person(directory_t* d, person_t* p);

void directory_stats(directory_t* d);

void directory_display(directory_t* d);


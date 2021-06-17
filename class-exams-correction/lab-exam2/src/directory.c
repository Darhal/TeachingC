#include "directory.h"

int hash(char *str, int n) {
    int hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    hash = ((hash % n) + n) % n;
    return hash;
}

person_t* person_create(const char* nom, const char* tel)
{
    person_t* p = malloc(sizeof(person_t));
    p->nom = strdup(nom);
    p->tel = strdup(tel);
    return p;
}

void person_destroy(person_t* p)
{
    free(p->nom);
    free(p->tel);
    free(p);
}

void person_display(person_t* p)
{
    printf("%s ; %s\n", p->nom, p->tel);
}


void add_arr(array* arr, person_t* p)
{
    arr->count++;
    arr->arr = realloc(arr->arr, arr->count * sizeof(person_t*));
    arr->arr[arr->count - 1] = p;
}

void destroy_arr(array* arr)
{
    if (arr->arr && arr->count){
        for (int i = 0; i < arr->count; i++){
        //    free(arr->person[i]);
        }
        
        free(arr->arr);
    }
}

directory_t* directory_create(int n)
{
    directory_t* d = malloc(sizeof(directory_t));
    d->count = n;
    d->tab_hash = calloc(d->count, sizeof(array));
    return d;
}

void directory_destroy(directory_t* d)
{
    for (int i = 0; i < d->count; i++) {
        destroy_arr(&d->tab_hash[i]);
    }

    free(d->tab_hash);
    free(d);
}

void directory_add_person(directory_t* d, person_t* p)
{
    int h = hash(p->nom, d->count);
    add_arr(&d->tab_hash[h], p);
}

void directory_stats(directory_t* d)
{
    printf("%d\n", d->count);
    for (int i = 0; i < d->count; i++) {
        printf("%d\n", d->tab_hash[i].count);
    }
}

void directory_display(directory_t* d)
{
    for (int i = 0; i < d->count; i++) {
        for (int j = 0; j < d->tab_hash[i].count; j++){
            person_display(d->tab_hash[i].arr[j]);
        }
    }
}

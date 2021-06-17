#include "book.h"
#include <stdlib.h>
#include <string.h>

static int hash_str(const char* str)
{
    int hash = 0xf0e1d2c3; // random init hash

    for (int i = 0; i < strlen(str); i++) {
        hash ^= (str[i] << (i % 23)); // shift str based on where we are in the str (no overflow bcuz of % 23)
    }

    return hash;
}

book* book_init(char* title, char* author)
{
    book* b = malloc(sizeof(book));
    b->id     = hash_str(title); // title is supposed to be unique
    b->title  = strdup(title);
    b->author = strdup(author);
    return b;
}

void book_destroy(book* self)
{
    // sanity cehck
    if (!self)
        return;

    if (self->author)
        free(self->author);
    if (self->title)
        free(self->title);
    
    free(self);
}

int book_get_id(book* self)
{
    return self->id;
}

char* book_get_title(book* self)
{
    return self->title;
}

char* book_get_author(book* self)
{
    return self->author;
}
#include "library.h"
#include <string.h>
#include <assert.h>
#include <stdlib.h>

library* library_init(int init_cap)
{
    library* lib = malloc(sizeof(library));
    lib->entries = calloc(init_cap, sizeof(entry));
    lib->size = 0;
    lib->capacity = init_cap;
    return lib;
}

void library_destroy(library* self)
{
    if (!self)
        return;

    // we shouldn't free books here ? I guess so....
    /*for (int i = 0; i < self->size; i++){
        // TODO: make sure that entries isnt a tab of ptrs
        book_destroy(self->entries[i].book);
    }*/

    if (self->entries)
        free(self->entries);
    
    free(self);
}

int library_books_count(library* self)
{
    return self->size;
}

void library_register_book(library* self, book* book)
{
    for (int i = 0; i < self->size; i++){
        char* cbname = book_get_title(self->entries[i].book);
        char* bname = book_get_title(book);

        if (!strcmp(bname, cbname)) { // they are eq
            self->entries[i].count++;
            return;
        }
    } 

    // if we reach here meaning we didnt find it so lets add it
    assert(self->size < self->capacity); // sanity check
    self->entries[self->size].book = book;
    self->entries[self->size].count = 1;
    self->size++;
}

book* library_find_by_id(library* self, int id)
{
    for (int i = 0; i < self->size; i++){
        int bid = book_get_id(self->entries[i].book);

        if (bid == id) {
            return self->entries[i].book;
        }
    } 

    return NULL;
}

book* library_find_by_title(library* self, char* title)
{
    for (int i = 0; i < self->size; i++){
        char* cbname = book_get_title(self->entries[i].book);

        if (!strcmp(cbname, title)) { // they are eq
            return self->entries[i].book;
        }
    } 

    return NULL;
}

int library_is_book_available(library* self, char* title) 
{
    for (int i = 0; i < self->size; i++){
        char* cbname = book_get_title(self->entries[i].book);

        if (!strcmp(cbname, title)) { // they are eq
            return self->entries[i].count;
        }
    }

    return 0;
}

book* library_borrow_book(library* self, char* title)
{
    for (int i = 0; i < self->size; i++){
        char* cbname = book_get_title(self->entries[i].book);

        if (!strcmp(cbname, title) && self->entries[i].count) { // they are eq
            self->entries[i].count--;
            return self->entries[i].book;
        }
    } 

    return NULL;
}

int library_return_book(library* self, book* book)
{
    for (int i = 0; i < self->size; i++){
        char* cbname = book_get_title(self->entries[i].book);
        char* bname = book_get_title(book);

        if (!strcmp(cbname, bname)) { // they are eq
            self->entries[i].count++;
            return self->entries[i].count;
        }
    } 

    return 0;
}

book** library_find_by_author(library* self, char* author)
{
    book** books = NULL;
    int count = 0;
    int cap = 4;
    
    for (int i = 0; i < self->size; i++){
        char* auth = book_get_author(self->entries[i].book);

        if (!strcmp(auth, author)) { // they are eq
            if (count >= cap || books == NULL) {
                cap *= 2;
                books = realloc(books, cap * sizeof(book*));
            }

            // printf("%d - %d\n", cap, count);
            books[count++] = self->entries[i].book;
        }
    } 

    return books;
}
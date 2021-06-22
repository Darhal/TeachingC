#pragma once

#include "book.h"

typedef struct _entry
{
    book* book;
    int count;
} entry;


typedef struct _library
{
    entry* entries;
    int capacity;
    int size;
} library;

library* library_init(int init_cap);

void library_destroy(library* self);

int library_books_count(library* self);

void library_register_book(library* self, book* book);

book* library_find_by_id(library* self, int id);

book* library_find_by_title(library* self, char* title);

int library_is_book_available(library* self, char* title);

book* library_borrow_book(library* self, char* title);

int library_return_book(library* self, book* book);

book** library_find_by_author(library* self, char* author);
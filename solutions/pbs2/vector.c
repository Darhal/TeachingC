#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "vector.h"

void init(vector* vec, size_t unit_size)
{
    assert(vec != NULL);

    vec->size = 0;
    vec->capacity = VECTOR_INIT_HALF_CAPACITY;
    vec->unit_size = unit_size;
    vec->elements = NULL;
}

size_t size(vector* vec)
{
    assert(vec != NULL);
    return vec->size;
}

size_t capacity(vector* vec)
{
    assert(vec != NULL);
    return vec->capacity;
}

void reserve(vector* vec, size_t capacity)
{
    assert(vec != NULL);

    if (capacity >= vec->capacity || !vec->elements) {
        vec->capacity = vec->capacity * 2;

        if (capacity > vec->capacity) {
            vec->capacity = capacity;
        }
        
        vec->elements = realloc(vec->elements, vec->capacity * vec->unit_size);
    }
}

void resize(vector* vec, size_t size)
{
    reserve(vec, size);
    vec->size = size;
}

void* get(vector* vec, size_t index)
{
    assert(vec != NULL);
    assert(vec->elements != NULL);
    assert(index < vec->size);
    return (void*)((char*)vec->elements + (index * vec->unit_size));
}

void* front(vector* vec)
{
    return get(vec, 0);
}

void* back(vector* vec)
{
    return get(vec, vec->size - 1);
}

void push_back(vector* vec, void* element)
{
    reserve(vec, vec->size + 1);

    void* last = (char*)vec->elements + vec->size * vec->unit_size;
    memcpy(last, element, vec->unit_size);
    vec->size++;
}

void push_front(vector* vec, void* element)
{
    reserve(vec, vec->size + 1);

    // shift all elements starting from the last element to the first
    for (size_t pos = vec->size; pos > 0; pos--) {
        void* src = (char*)vec->elements + (pos - 1) * vec->unit_size;
        void* dst = (char*)vec->elements + pos * vec->unit_size;
        memcpy(dst, src, vec->unit_size);
    }

    // Place element in the first slot
    memcpy(vec->elements, element, vec->unit_size);
    vec->size++;
}

void insert(vector* vec, size_t index, void* element)
{
    reserve(vec, vec->size + 1);
    assert(index <= vec->size);

    // shift all elements starting from the last element to the pos
    for (size_t pos = vec->size; pos > index; pos--) {
        void* src = (char*)vec->elements + (pos - 1) * vec->unit_size;
        void* dst = (char*)vec->elements + pos * vec->unit_size;
        memcpy(dst, src, vec->unit_size);
    }

    void* indexMemorySlot = (char*)vec->elements + index * vec->unit_size;
    memcpy(indexMemorySlot, element, vec->unit_size);
    vec->size++;
}

void shrink_to_fit(vector* vec)
{
    assert(vec != NULL);
    vec->elements = realloc(vec->elements, vec->size * vec->unit_size);
    vec->capacity = vec->size;
}

void destroy(vector* vec)
{
    assert(vec != NULL);

    if (vec->elements) {
        free(vec->elements);
        vec->elements = 0;
        vec->size = 0;
    }
}
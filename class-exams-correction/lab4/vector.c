#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "vector.h"

void vec_init(vector* vec, size_t unit_size)
{
    assert(vec != NULL);

    vec->size = 0;
    vec->capacity = VECTOR_INIT_HALF_CAPACITY;
    vec->unit_size = unit_size;
    vec->elements = NULL;
}

vector vec_init2(size_t unit_size)
{
    vector vec;
    vec.size = 0;
    vec.capacity = VECTOR_INIT_HALF_CAPACITY;
    vec.unit_size = unit_size;
    vec.elements = NULL;
    return vec;
}

vector vec_copy(const vector* other)
{
    vector vec;
    vec.capacity = other->capacity;
    vec.unit_size = other->unit_size;
    vec.size = other->size;
    vec.elements = malloc(vec.unit_size * vec.capacity);
    memcpy(vec.elements, other->elements, vec.unit_size * vec.size);
    return vec;
}

void* vec_find(const vector* vec, const void* element)
{
    for (size_t i = 0; i < vec->size; i++) {
        void* current = vec_get(vec, i);

        if (memcmp(current, element, vec->unit_size) == 0) {
            return current;
        }
    }

    return NULL;
}

void vec_pop_back(vector* vec)
{
    if (vec->size > 0)
        vec->size--;
}

size_t vec_size(const vector* vec)
{
    assert(vec != NULL);
    return vec->size;
}

size_t vec_capacity(const vector* vec)
{
    assert(vec != NULL);
    return vec->capacity;
}

void vec_reserve(vector* vec, size_t capacity)
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

void vec_resize(vector* vec, size_t size)
{
    vec_reserve(vec, size);
    vec->size = size;
}

void* vec_get(const vector* vec, size_t index)
{
    assert(vec != NULL);
    assert(vec->elements != NULL);
    assert(index < vec->size);
    return (void*)((char*)vec->elements + (index * vec->unit_size));
}

void* vec_front(const vector* vec)
{
    return vec_get(vec, 0);
}

void* vec_back(const vector* vec)
{
    return vec_get(vec, vec->size - 1);
}

void vec_push_back(vector* vec, const void* element)
{
    vec_reserve(vec, vec->size + 1);

    void* last = (char*)vec->elements + vec->size * vec->unit_size;
    memcpy(last, element, vec->unit_size);
    vec->size++;
}

void vec_push_front(vector* vec, const void* element)
{
    vec_reserve(vec, vec->size + 1);

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

void vec_insert(vector* vec, size_t index, const void* element)
{
    vec_reserve(vec, vec->size + 1);
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

void vec_shrink_to_fit(vector* vec)
{
    assert(vec != NULL);
    vec->elements = realloc(vec->elements, vec->size * vec->unit_size);
    vec->capacity = vec->size;
}

void vec_destroy(vector* vec)
{
    assert(vec != NULL);

    if (vec->elements) {
        free(vec->elements);
        vec->elements = 0;
        vec->size = 0;
    }
}
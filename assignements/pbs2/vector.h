#include <stdint.h>
#include <stddef.h>

#define VECTOR_INIT_CAPACITY 8

typedef struct vector_t
{
    void*   elements;
    size_t  size;
    size_t  capacity;
    size_t  unit_size;
} vector;

void init(vector* vec, size_t unit_size);

size_t size(vector* vec);

size_t capacity(vector* vec);

void* get(vector* vec, size_t index);

void* front(vector* vec);

void* back(vector* vec);

void push_back(vector* vec, void* element);

void push_front(vector* vec, void* element);

void insert(vector* vec, size_t index, void* element);

void resize(vector* vec, size_t size);

void reserve(vector* vec, size_t capacity);

void shrink_to_fit(vector* vec);

void destroy(vector* vec);

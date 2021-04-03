#include <stdint.h>
#include <stddef.h>

#define VECTOR_INIT_HALF_CAPACITY 4

typedef struct vector_t
{
    void*   elements;
    size_t  size;
    size_t  capacity;
    size_t  unit_size;
} vector;


/**
 * Initilise the vector struct by setting :
 * unit_size to the unit_size given in the arguments
 * elements array to NULL (empty)
 * size to 0
 * capacity to VECTOR_INIT_HALF_CAPACITY
 * */
void init(vector* vec, size_t unit_size);


/**
 * returns the size of vec
 * */
size_t size(vector* vec);


/**
 * returns the capacity of vec
 * */
size_t capacity(vector* vec);

/**
 * If vec->capacity is less then the given capacity or vec->elements is NULL then
 *      vec->capacity is updated to be vec->capacity * 2
 *      if capacity is still less than vec->capacity then vec->capacity must be capacity
 *      vec->elements must now point to a newly allocated memory that can contain vec->capacity elements
 *      the elemens existing in the older vec->elements must be copied over to the new vec->elements
 * Otherwise nothing happens
 * */
void reserve(vector* vec, size_t capacity);


/**
 * Sets vec size to the size given in the argument
 * If the given size exceeds vec->capacity then
 * elements must be reallocated to be able to contain
 * (2 * size) elements. The elements already present
 * must be copied to the new array.
 * */
void resize(vector* vec, size_t size);


/**
 * return a pointer the element at the index given by the argument
 * if the index is out of bound an assertion occurs
 * */
void* get(vector* vec, size_t index);


/**
 * returns a pointer to the first element in vec
 * if vec is empty then it asserts
 * */
void* front(vector* vec);


/**
 * returns a pointer to the last element in vec
 * if vec is empty then it asserts
 * */
void* back(vector* vec);


/**
 * Add the element given in the arguments to the last cell of vec
 * The content of the argument element must be copied (dont just store the pointer)
 * Also handles the case where capacity is exceeded
 * */
void push_back(vector* vec, void* element);


/**
 * Add the element given in the argments to the first cell of vec
 * The content of the argument element must be copied (dont just store the pointer)
 * Also handles the case where capacity is exceeded
 * The already existing elements are shifted to the right by one cell
 * */
void push_front(vector* vec, void* element);

/**
 * Inserts the element given in the argments to the cell of index 'index'
 * The content of the argument element must be copied (dont just store the pointer)
 * Also handles the case where capacity is exceeded
 * The already existing elements that are the right of 'index' are shifted to the right 
 * by one cell
 * */
void insert(vector* vec, size_t index, void* element);

/**
 * Changes the capacity of vec to be the same as its size
 * And frees all the extra memory (the memory that is not used)
 * */
void shrink_to_fit(vector* vec);

/**
 * frees the memory allocated by vec (if no memory is allocated then it does nothing)
 * sets its size to 0
 * sets the pointer elements to NULL
 * */
void destroy(vector* vec);

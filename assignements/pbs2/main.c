#include <stdio.h>
#include <assert.h>
#include "vector.h"

void print_info(vector* vec)
{
    printf("capacity: %zu | size: %zu | array: [ ", vec->capacity, vec->size);
    for (size_t i = 0; i < vec->size; i++) {
        int* currentElement = (int*)((char*)vec->elements + i * vec->unit_size);
        printf("%d ", *currentElement);
    }
    printf("]\n");
}

void test_case1()
{
    vector v;
    init(&v, sizeof(int));

    assert(v.capacity == VECTOR_INIT_HALF_CAPACITY);
    assert(v.size == 0);
    assert(v.unit_size == sizeof(int));
    assert(v.elements == NULL);

    assert(v.capacity == capacity(&v));
    assert(v.size == size(&v));

    for (int i = 1; i <= 7; i++){
        push_back(&v, &i);
    }
    // print_info(&v);

    assert(size(&v) == 7);
    for (int i = 0; i < 7; i++) {
        assert(*((int*)get(&v, i)) == i + 1);
    }

    int tmp = 100;
    insert(&v, size(&v), &tmp);
    //print_info(&v);

    assert(size(&v) == 8);
    for (int i = 0; i < 7; i++) {
        assert(*((int*)get(&v, i)) == i + 1);
    }
    assert(*((int*)get(&v, 7)) == 100);
    assert(*((int*)get(&v, 7)) == *((int*)back(&v)));


    tmp = 69;
    push_front(&v, &tmp);
    //print_info(&v);

    assert(size(&v) == 9);
    assert(*((int*)front(&v)) == 69);
    assert(*((int*)get(&v, 0)) == *((int*)front(&v)));
    assert(*((int*)get(&v, 8)) == 100);
    assert(*((int*)get(&v, 8)) == *((int*)back(&v)));
    for (int i = 1; i < 7; i++) {
        assert(*((int*)get(&v, i)) == i);
    }

    

    tmp = 70;
    push_back(&v, &tmp);
    //print_info(&v);

    assert(size(&v) == 10);

    assert(*((int*)front(&v)) == 69);
    assert(*((int*)get(&v, 0)) == *((int*)front(&v)));
    assert(*((int*)get(&v, 8)) == 100);
    assert(*((int*)back(&v)) == 70);
    assert(*((int*)get(&v, 9)) == *((int*)back(&v)));
    for (int i = 1; i < 7; i++) {
        assert(*((int*)get(&v, i)) == i);
    }

    destroy(&v);

    assert(size(&v) == 0);
    assert(v.elements == NULL);
}

void test_case2()
{
    vector v;
    init(&v, sizeof(int));

    int tmp = 0;

    for (int i = 0; i < 100; i++) {
        if (i % 2){
            push_back(&v, &i);
        }else{
            push_front(&v, &i);
        }
    }

    int mustbe = 98;
    for (int i = 0; i < 50; i++) {
        assert(*(int*)get(&v, i) == mustbe);
        mustbe -= 2;
    }
    mustbe = 1;
    for (int i = 50; i < 100; i++) {
        assert(*(int*)get(&v, i) == mustbe);
        mustbe += 2;
    }

    shrink_to_fit(&v);

    assert(size(&v) == capacity(&v));
    mustbe = 98;
    for (int i = 0; i < 50; i++) {
        assert(*(int*)get(&v, i) == mustbe);
        mustbe -= 2;
    }
    mustbe = 1;
    for (int i = 50; i < 100; i++) {
        assert(*(int*)get(&v, i) == mustbe);
        mustbe += 2;
    }

    // print_info(&v);
    destroy(&v);

    assert(size(&v) == 0);
    assert(v.elements == NULL);
}

void test_case3()
{
    vector v;
    init(&v, sizeof(int));

    unsigned int cap = 1 << 28; // 2**28  = 268435456 elements 
    resize(&v, cap);            // 2**28 * 4 = 1 GB of data
    assert(size(&v) == cap);
    assert(capacity(&v) == cap);

    for (int i = 0; i < cap; i++) {
        *(int*)(get(&v, i)) = i;
    }

    for (int i = 0; i < cap; i++) {
        assert(*(int*)(get(&v, i)) == i);
    }


    push_back(&v, &cap);

    assert(capacity(&v) == cap * 2);
    assert(*(int*)(back(&v)) == cap);

    shrink_to_fit(&v);

    assert(capacity(&v) == cap + 1);
    assert(size(&v) == cap + 1);
    assert(*(int*)(back(&v)) == cap);

    destroy(&v);
    assert(size(&v) == 0);
    assert(v.elements == NULL);
}

int main()
{
    test_case1();
    test_case2();
    test_case3();

    printf("\033[0;32m*** ALL TESTS PASSED! ***\n");
}
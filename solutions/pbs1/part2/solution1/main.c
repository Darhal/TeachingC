#include <stdlib.h>
#include <stdio.h> 
#include <stdint.h> // for UINT32_MAX
#include <assert.h> // for testing

unsigned int clz(unsigned int b)
{
    unsigned int count = 0;
    int mask_pos = 31;
    
    while ( (mask_pos > 0) && !(b & (1 << mask_pos)) ) {
        count++;
        mask_pos--;
    }

    return count;
}

unsigned int nextpow2(unsigned n)
{
    int power = 1;
    while(power < n)
        power *= 2; // Another faster alternative is to use this instead: power <<= 1;
    return power;
}

unsigned int log2i(unsigned n)
{
    int log2 = 0;
    if (n == 1) 
        return log2;
    
    while (n) {
        n /= 2; // Another faster alternative is to use this instead: n >>= 1;
        log2++;
    }

    return log2;
}

int main()
{
    // Must be compiled with gcc or clang since we used __builtin_clz
    // Testing clz :
    for (unsigned i = 1; i < UINT32_MAX; i++)
        assert(clz(i) == __builtin_clz(i));

    // testing nextpow2 and log2i
    unsigned test_values[] = { 1, 3, 5, 31, 120 };
    unsigned pow2_values[] = { 1, 4, 8, 32, 128 };
    unsigned log2_values[] = { 0, 2, 3, 5, 7 };

    assert(nextpow2(0) == 1); // special case log2i(0) doesnt exist

    for (unsigned i = 0; i < sizeof(test_values) / sizeof(unsigned); i++) {
        printf("%u - %u - %u\n", test_values[i], nextpow2(test_values[i]), log2i(test_values[i]));
        assert(nextpow2(test_values[i]) == pow2_values[i]);
        assert(log2i(test_values[i]) == log2_values[i]);
    }
}
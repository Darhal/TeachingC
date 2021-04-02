#include <stdlib.h>
#include <stdio.h> 
#include <stdint.h> // for UINT32_MAX
#include <assert.h> // for testing

#define CHAR_BIT 8

unsigned int clz(unsigned int b)
{
    if (!b) return 32;

    unsigned int count = 0;
    int mask_pos = 31;
    
    while ( (mask_pos > 0) && !(b & (1 << mask_pos)) ) {
        count++;
        mask_pos--;
    }

    return count;
    // Notes:
    // Might also want to use __builtin_clz (but this only works on GCC/Clang)
    // so the whole function would be:
    // return __builtin_clz(b)
}

unsigned int nextpow2(unsigned n)
{
    return 1 << (32 - clz(n - 1));
}

// Another alternative is to use this from: https://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2
unsigned int nextpow2v2(unsigned n)
{
    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n++;
    n += (n == 0); // case of n = 0
    return n;
}

unsigned int log2i(unsigned n)
{
    return 32 - clz(nextpow2(n)) - 1;
}

int main()
{
    // Must be compiled with gcc or clang since we used __builtin_clz
    // Testing clz :
    for (unsigned i = 1; i < UINT32_MAX; i++)
        assert(clz(i) == __builtin_clz(i));

    // testing nextpow2 and log2i
    unsigned test_values[] = { 1, 3, 4, 5, 8, 31, 120 };
    unsigned pow2_values[] = { 1, 4, 4, 8, 8, 32, 128 };
    unsigned log2_values[] = { 0, 2, 2, 3, 3, 5, 7 };

    assert(nextpow2(0) == 1); // special case log2i(0) doesnt exist
    assert(nextpow2v2(0) == 1); // special case log2i(0) doesnt exist

    for (unsigned i = 0; i < sizeof(test_values) / sizeof(unsigned); i++) {
        // printf("%u - %u - %u\n", test_values[i], nextpow2(test_values[i]), log2i(test_values[i]));
        assert(nextpow2(test_values[i]) == pow2_values[i]);
        assert(nextpow2v2(test_values[i]) == pow2_values[i]);
        assert(log2i(test_values[i]) == log2_values[i]);
    }
}
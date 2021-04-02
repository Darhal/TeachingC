#include <stdlib.h>
#include <stdio.h> 
#include <stdint.h> // for UINT32_MAX
#include <assert.h> // for testing

// Method 1 (recursive):
unsigned gcd_rec(unsigned a, unsigned b)
{
    if (a == 0)
        return b;
    return gcd_rec(b % a, a);
}

// Method 2 (iterative):
unsigned gcd(unsigned a, unsigned b)
{
    unsigned r;
    while(b!=0){
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int main()
{
    struct pair
    {
        unsigned a;
        unsigned b;
    };

    // testing gcd
    struct pair test_values[] = { {1, 3}, {3, 5}, {6, 8}, {8, 32}, {30, 120} };
    unsigned expected[] = {1, 1, 2, 8, 30};

    for (unsigned i = 0; i < sizeof(test_values) / sizeof(struct pair); i++)
        assert( gcd_rec(test_values[i].a, test_values[i].b) == expected[i] && 
                gcd(test_values[i].a, test_values[i].b) == expected[i]
        );
}
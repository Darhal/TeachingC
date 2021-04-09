#pragma once

// clz implementation
static unsigned int clz_sol(unsigned int b)
{
    if (!b) return 32;
    unsigned int count = 0;
    int mask_pos = 31;
    
    while ( (mask_pos > 0) && !(b & (1 << mask_pos)) ) {
        count++;
        mask_pos--;
    }

    return count;
}

#pragma once

#include <stdlib.h>

static void** mat_init_sol(unsigned N, unsigned M, unsigned unit_size)
{
    void** mat = malloc(N * sizeof(void*));
    void* mat_internal = malloc(N * M * unit_size);

    for (int i = 0; i < N; i++) {
        mat[i] = (char*)mat_internal + i * M * unit_size;
    }

    return mat;
}

static void mat_free_sol(void** mat)
{
    free((void*)*mat);
    free(mat);
}
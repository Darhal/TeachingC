#include <stdlib.h>

void** mat_init(unsigned N, unsigned M, unsigned unit_size)
{
    void** mat = malloc(N * sizeof(void*));
    void* mat_internal = malloc(N * M * unit_size);

    for (int i = 0; i < N; i++) {
        mat[i] = (char*)mat_internal + i * M * unit_size;
    }

    return mat;
}

void mat_free(void** mat)
{
    free(((char**)mat)[0]);
    free(mat);
}
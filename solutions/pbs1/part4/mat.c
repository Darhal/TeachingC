#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <string.h>

// Methode 1:
// Avantages: simple
// Inconvinient: 
//      - plein d'allocation (N*M)
//      - n'est pas cache friendly
//      - free en O(N)
int** mat1(int N, int M)
{
    int** m = (int**)malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++){
        m[i] = (int*)malloc(M * sizeof(int));
    }
    return m;
}

void free_mat1(int** mat, int N, int M)
{
    for (int i = 0; i < N; i++){
        free(mat[i]);
    }
    free(mat);
}

// Methode 2:
// Avantages:
//  - un peu plus cache friendly que la methode 1
//  - simple à traiter
//  - 2 alloc seulement
//  - version améliorer de mat1
//  - free en O(2)
// Inconvinient: O(N)
int** mat2(int N, int M)
{
    int** mat = (int**)malloc(N * sizeof(int*));
    int* mat_internal = (int*)malloc(N * M * sizeof(int));
    for (int i = 0; i < N; i++){
        mat[i] = mat_internal + i * M;
    }
    return mat;
}

void free_mat2(int** mat, int N)
{
    free(mat[0]);
    free(mat);
}

// Methode 3:
// Avantages: 
//  - cache friendly
//  - une seul alloc, un seul free
// Inconvinient: un peu plus dur à traiter
int* mat3(int N, int M)
{
    int* m = (int*)malloc(M * N * sizeof(int));
    return m;
}

void free_mat3(int* mat)
{
    free(mat);
}

int main()
{
    return EXIT_SUCCESS;
}
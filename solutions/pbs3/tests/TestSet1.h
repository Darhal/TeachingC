#pragma once

#include <time.h>
#include "common.h"
#include "../utils.h"

/**
 * Tests the clz function
 */ 
static void Set1_TestCase1()
{
    srand(time(NULL));
    
    for (int i = 0; i < 1000; i++) {
        unsigned c = rand();
        unsigned sol = clz_sol(c);
        unsigned candidat = clz(c);

        if (sol != candidat) {
            printf(RED("\tTest Case #1 : FAILED (arg : %u expected %u as a result got %u)"), c, sol, candidat);
            fflush(stdout);
            assert(0);
        }
        
    }

    puts(GREEN("\tTest Case #1 : PASSED"));
}

/**
 * Tests the matrix functions
 */ 
static void Set1_TestCase2()
{
    srand(time(NULL));
    
    for (int i = 0; i < 1000; i++) {
        unsigned N = rand() % 50;
        unsigned M = rand() % 50;
        N = N ? N : 100;
        M = M ? M : 100;

        int** mat_cand = (int**)mat_init(N, M, sizeof(int));

        for (int n = 0; n < N; n++) {
            for (int m = 0; m < M; m++) {
                mat_cand[n][m] = n ^ m;
            }
        }

        mat_free((void**)mat_cand);
    }

    puts(GREEN("\tTest Case #2 : PASSED"));
}

/**
 * Tests the calc_neighbours functions
 */ 
static void Set1_TestCase3()
{
    for (int i = 3; i < 1000; i+=2) {
        vec2* sol = calc_neighbours_sol(i);
        vec2* candidat = calc_neighbours(i);

        for (int j = 0; j < i * i; j++) {
            if (sol[j].x != candidat[j].x || sol[j].y != candidat[j].y) {
                printf(RED("\tTest Case #2 : FAILED (arg : %u expected (%u, %u) as a result got (%u, %u) at index %u)"), i, sol[j].y, sol[j].x, candidat[j].y, candidat[j].x, j);
                fflush(stdout);
                assert(0);
            }
        }

        free(sol);
        free(candidat);
    }

    puts(GREEN("\tTest Case #3 : PASSED"));
}

static void TesetSet1()
{
    printf("Test Set #1 : \n");
    Set1_TestCase1();
    Set1_TestCase2();
    Set1_TestCase3();
    puts(GREEN("\tTest Set #1  : PASSED"));
}
#pragma once
#include <stdlib.h>

// *** Questions related to PART 3 ***

// DONT CHANGE THESE INCLUDES ALSO DONT SPOIL THE EXERCICE 
// AND DONT LOOK INTO THESE FILES EITHER
#include "clz/clz.h"
#include "matrix/matrix.h"
#include "neighbours/neighbours.h"

static unsigned int clz(unsigned int b) {
    // TODO : Implement this
    // Define your own clz implementation here
    // or alternatively uncomment the line below and you will be able to use it
    return clz_sol(b);
    return 0;
}

/**
* Allocates memory for N by M matrix that contain elements of unit_size bytes
*/ 
static void** mat_init(unsigned N, unsigned M, unsigned unit_size)
{    
    // TODO : Implement this
    // Define your own matrix implementation here
    // or alternatively uncomment the line below and you will be able to use it
    return mat_init_sol(N, M, unit_size);
    return NULL;
}

/**
* Frees the memory allocated by mat_init
*/
static void mat_free(void** mat)
{
    // TODO : Implement this
    // Define your own matrix implementation here
    // or alternatively uncomment the line below and you will be able to use it
    return mat_free_sol(mat);
}

/**
 * Given an impair kernel_size calc_nehgbours will return the (y, x) coordinates relative
 * to the central cell. This function returns the coordinates in a linear array where
 * the first element is the coordiante of the top left cell going from left to right and from
 * top to bottom
 * The vec2 type is defined as :
 * typedef struct vec2_t { int y, x; } vec2;
 */ 
static vec2* calc_neighbours(unsigned kernel_size) {
    // Define your own calc_neighbours implementation here
    // or alternatively uncomment the line below and you will be able to use it
    return calc_neighbours_sol(kernel_size);
    return NULL;
}


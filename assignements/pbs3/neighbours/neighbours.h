#pragma once

#include <stdlib.h>
#include "../vec2.h"

/**
 * Given an impair kernel_size calc_nehgbours will return the (y, x) coordinates relative
 * to the central cell. This function returns the coordinates in a linear array where
 * the first element is the coordiante of the top left cell going from left to right and from
 * top to bottom
 */ 
static vec2* calc_neighbours(unsigned kernel_size)
{
    vec2* neighbours = malloc(kernel_size * kernel_size * sizeof(vec2));
    int step = (kernel_size - 1) / 2;

    for (int i = 0; i < kernel_size; i++) {
        for (int j = 0; j < kernel_size; j++) {
            neighbours[i + j * kernel_size].y = -step + i;
            neighbours[i + j * kernel_size].x = -step + j;
        }
    }

    return neighbours;
}
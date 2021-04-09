#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "image.h"
#include "matrix.h"
#include "vec2.h"

// Define your own clz implementation here (dont forget to declare it static !)
// or alternatively uncomment the line below and you will be able to use it
// #include "clz/clz.h"
// If you want to implement the function complete the lines below
// static unsigned int clz(unsigned int b) {}

// Define your own calc_neighbours implementation here (dont forget to declare it static !)
// or alternatively uncomment the line below and you will be able to use it
// #include "neighbours/neighbours.h"
// If you want to implement the function complete the lines below
// static vec2* calc_neighbours(unsigned kernel_size) {}


image init_image(unsigned width, unsigned height)
{
    // TODO: Implement this
}

image convert_to_image(const bmp* const bmp)
{
    // TODO: Implement this
}

image copy_image(const image* const img)
{
    // TODO: Implement this
}

void grayscale_image(image* img)
{
    // TODO: Implement this
}

void apply_filter(image* dst, image* src, unsigned kernel_size, float* kernel)
{
    // Kernel size must be impair!
    assert(kernel_size % 2 == 1);
    vec2* neighbours = calc_neighbours(kernel_size);

    // TODO : Finish this implementation

    free(neighbours);
}

void save_raw(const image* const img, const char* name)
{
    // TODO: Implement this
}
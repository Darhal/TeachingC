#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "image.h"
#include "utils.h"

// *** Questions related to PART 3 ***

image init_image(unsigned width, unsigned height)
{
    image img;
    // TODO: Implement this
    return img;
}

void destroy_image(image* img)
{
    // TODO: Implement this
}

image convert_to_image(const bmp* const bmp)
{
    image img;
    // TODO: Implement this
    return img;
}

image copy_image(const image* const img)
{
    image copy;
    // TODO: Implement this
    return copy;
}

void grayscale_image(image* img)
{
    // TODO: Implement this
}

void apply_filter(image* dst, image* src, unsigned kernel_size, const float* kernel)
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
#pragma once
#include "bmp_loader.h"

typedef struct rgb_t
{
    unsigned char r, g, b;
} rgb;

typedef struct image_t
{
    rgb**    colors;
    unsigned width, height;
} image;

/**
 * Initialize an image by setting width and height
 * and allocating the colors matrix
 */
image init_image(unsigned width, unsigned height);

/**
 * Takes a bmp const pointer and converts it to an image object
 * In order to do this the width, height and the pixels matrix 
 * must be copied over to the image struct
 */ 
image convert_to_image(const bmp* const bmp);

/**
 * Copy an existing image to another one
 */ 
image copy_image(const image* const img);

/**
 * Converts an image to grayscale this can be done by averaging
 * the R, G and B component of each pixel
 */
void grayscale_image(image* img);

/**
 * Applies a convolution product between the source image and the kernel
 * It stores the result in the destination image 
 */
void apply_filter(image* dst, image* src, unsigned kernel_size, const float* kernel);

/**
 * Converts an image to grayscale this can be done by averaging
 * the R, G and B component of each pixel
 */
void save_raw(const image* const img, const char* name);

/**
 * Liberates the memory related to the image object
 */ 
void destroy_image(image* img);
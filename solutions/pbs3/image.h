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


image init_image(unsigned width, unsigned height);

image convert_to_image(const bmp* const bmp);

image copy_image(const image* const img);

void grayscale_image(image* img);

void apply_filter(image* dst, image* src, unsigned kernel_size, float* kernel);

void save_raw(const image* const img, const char* name);
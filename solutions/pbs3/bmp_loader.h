#pragma once

#include <stdio.h>

typedef struct bmp_header_t
{
    char signature[2];
    unsigned int file_size;
    unsigned char junk[4];      // not used 
    unsigned int offset_pixels;
} bmp_header;

typedef struct bmp_dib_header_t 
{
    unsigned int header_size;
    unsigned int width;
    unsigned int height;
    unsigned short planes, bpp;
    unsigned int red_bitmask, green_bitmask, blue_bitmask, alpha_bitmask;
} bmp_dib_header;


typedef struct bmp_t
{
    bmp_header header;
    bmp_dib_header dib_header;
    unsigned int** pixels; 
} bmp;

void bmp_load(bmp* bmp, FILE* file);

void bmp_load_header(bmp_header* header,  FILE* file);

void bmp_load_dib_header(bmp_dib_header* dib_header, FILE* file);

void bmp_load_pixels(const bmp_dib_header* const dib, unsigned** pixels, FILE* file);

void bmp_print_info(const bmp* const bmp);
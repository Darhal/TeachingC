#pragma once

#include <stdio.h>

typedef struct bmp_header_t
{
    char signature[2];
    unsigned int file_size;
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

/**
 * Takes a pointer to a bmp struct and a filename
 * It opens the file calls bmp_load_header which 
 * loads in the header, then verify that its a BMP 
 * file, it asserts if its not. otherwise it proceeds
 * to call bmp_load_dib_header and then bmp_load_pixels.
 * Then it finally closes the file
 */
void bmp_load(bmp* bmp, const char* filename);

/**
 * Takes a pointer to the bmp_header and a FILE pointer
 * It read relevant data from the file and fills the relevant
 * bmp_header fields with the necessary data
 */
void bmp_load_header(bmp_header* header,  FILE* file);

/**
 * Takes a pointer to the bmp_dib_header and a FILE pointer
 * It read relevant data from the file and fills the relevant
 * bmp_dib_header fields with the necessary data
 */
void bmp_load_dib_header(bmp_dib_header* dib_header, FILE* file);

/**
 * Takes a pointer to the bmp_dib_header, a pixels matrix and a FILE pointer
 * It read the pixel data from the file and then it fills the pixels matrix
 */
void bmp_load_pixels(const bmp_dib_header* const dib, unsigned** pixels, FILE* file);

/**
 * Liberates the memory used in the bmp object
 */ 
void bmp_destroy(bmp* bmp);

/**
 * This is a function that prints important informations about the bmp.
 * It's is already written and you can use it for debugging purposes
 */
void bmp_print_info(const bmp* const bmp);
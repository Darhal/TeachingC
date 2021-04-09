#include <assert.h>
#include "bmp_loader.h"
#include "matrix.h"

void bmp_load(bmp* bmp, const char* filename)
{    
    // TODO : Implement this !
}

void bmp_load_header(bmp_header* header,  FILE* file)
{
    // TODO : Implement this !
}

void bmp_load_dib_header(bmp_dib_header* dib_header, FILE* file)
{
    // TODO : Implement this !
}

void bmp_load_pixels(const bmp_dib_header* const dib, unsigned** pixels, FILE* file)
{
    // TODO : Implement this !
}

void bmp_print_info(const bmp* const bmp)
{
    const bmp_header* const header = &bmp->header;
    const bmp_dib_header* const dib_header = &bmp->dib_header;

    printf("File size        : %u\n", header->file_size);
    printf("Offset to pixels : %u\n", header->offset_pixels);
    printf("Width            : %u\n", dib_header->width);
    printf("Height           : %u\n", dib_header->height);
    printf("Planes           : %u\n", dib_header->planes);
    printf("BPP              : %u\n", dib_header->bpp);
    printf("Red bitmask      : %u\n", dib_header->red_bitmask);
    printf("Green bitmask    : %u\n", dib_header->green_bitmask);
    printf("Blue bitmask     : %u\n", dib_header->blue_bitmask);
    printf("Alpha bitmask    : %u\n", dib_header->alpha_bitmask);
}
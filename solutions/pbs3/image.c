#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "image.h"
#include "matrix.h"

static unsigned int clz(unsigned int b)
{
    if (!b) return 32;
    unsigned int count = 0;
    int mask_pos = 31;
    
    while ( (mask_pos > 0) && !(b & (1 << mask_pos)) ) {
        count++;
        mask_pos--;
    }

    return count;
}

image init_image(unsigned width, unsigned height)
{
    image result;
    result.width = width;
    result.height = height;
    result.colors = (rgb**)mat_init(result.height, result.width, sizeof(rgb));
    return result;
}

image convert_to_image(const bmp* const bmp)
{
    image img;
    img.width = bmp->dib_header.width;
    img.height = bmp->dib_header.height;
    img.colors = (rgb**)mat_init(img.height, img.width, sizeof(rgb));

    const unsigned shiftR = 32 - clz(bmp->dib_header.red_bitmask    >> 8);
    const unsigned shiftG = 32 - clz(bmp->dib_header.green_bitmask  >> 8);
    const unsigned shiftB = 32 - clz(bmp->dib_header.blue_bitmask   >> 8);
 
    printf("Shift r: %d\n", shiftR);
    printf("Shift g: %d\n", shiftG);
    printf("Shift b: %d\n", shiftB);
    printf("Shift a: %d\n", (32 - clz(bmp->dib_header.alpha_bitmask >> 8)));

    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            img.colors[y][x].r = (bmp->pixels[y][x] & bmp->dib_header.red_bitmask)   >> shiftR;
            img.colors[y][x].g = (bmp->pixels[y][x] & bmp->dib_header.green_bitmask) >> shiftG;
            img.colors[y][x].b = (bmp->pixels[y][x] & bmp->dib_header.blue_bitmask)  >> shiftB;
        }
    }

    return img;
}

image copy_image(const image* const img)
{
    image result;
    result.width = img->width;
    result.height = img->height;
    result.colors = (rgb**)mat_init(result.height, result.width, sizeof(rgb));

    for (int y = 0; y < result.height; y++) {
        for (int x = 0; x < result.width; x++) {
            result.colors[y][x] = img->colors[y][x];
        }
    }

    return result;
}

void grayscale_image(image* img)
{
    for (int y = 0; y < img->height; y++) {
        for (int x = 0; x < img->width; x++) {
            img->colors[y][x].r = (img->colors[y][x].r + img->colors[y][x].g + img->colors[y][x].b) / 3;
            img->colors[y][x].g = img->colors[y][x].r;
            img->colors[y][x].b = img->colors[y][x].r;
        }
    }
}

void apply_filter(image* dst, image* src, unsigned kernel_size, float* kernel)
{
    // Kernel size must be impair!
    assert(kernel_size % 2 == 1);

    typedef struct vec2_t { int y, x; } vec2;

    /*const vec2 neighbours[] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},  {0, 0},  {0, 1},
        {1, -1},  {1, 0},  {1, 1},
    };*/

    vec2* neighbours = malloc(kernel_size * kernel_size * sizeof(vec2));
    int step = (kernel_size - 1) / 2;

    for (int i = 0; i < kernel_size; i++) {
        for (int j = 0; j < kernel_size; j++) {
            neighbours[i + j * kernel_size].y = -step + i;
            neighbours[i + j * kernel_size].x = -step + j;

            printf("(%d,%d) ", neighbours[i + j * kernel_size].y, neighbours[i + j * kernel_size].x);
        }

        printf("\n");
    }

    for (int y = 0; y < src->height; y++) {
        for (int x = 0; x < src->width; x++) {
            float r = 0.f;
            float g = 0.f;
            float b = 0.f;

            for (int i = 0; i < kernel_size * kernel_size; i++) {
                const vec2 off = neighbours[i];
                vec2 coord = { y + off.y, x + off.x };

                if ((coord.y >= 0 && coord.y < src->height) && (coord.x >= 0 && coord.x < src->width)) {
                    unsigned nx = coord.x;
                    unsigned ny = coord.y;

                    r += ((float)src->colors[ny][nx].r/255.f) * kernel[i];
                    g += ((float)src->colors[ny][nx].g/255.f) * kernel[i];
                    b += ((float)src->colors[ny][nx].b/255.f) * kernel[i];
                }
            }

            r = r < 0.f ? 0.f : r;
            g = g < 0.f ? 0.f : g;
            b = b < 0.f ? 0.f : b;
            dst->colors[y][x].r = r * 255.f;
            dst->colors[y][x].g = g * 255.f;
            dst->colors[y][x].b = b * 255.f;
        }
    }

    free(neighbours);
}

void save_raw(const image* const img, const char* name)
{
    FILE* wfp = fopen(name, "wb");

    for (int y = 0; y < img->height; y++) {
        for (int x = 0; x < img->width; x++) {
            const unsigned char alpha = 0xFF;
            fwrite(&img->colors[y][x].b, sizeof(unsigned char), 1, wfp);
            fwrite(&img->colors[y][x].g, sizeof(unsigned char), 1, wfp);
            fwrite(&img->colors[y][x].r, sizeof(unsigned char), 1, wfp);
            fwrite(&alpha, sizeof(unsigned char), 1, wfp);
        }
    }

    fclose(wfp);
}
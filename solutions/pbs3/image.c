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
    img.width = width;
    img.height = height;
    img.colors = (rgb**)mat_init(img.height, img.width, sizeof(rgb));

    return img;
}

void destroy_image(image* img)
{
    // TODO: Implement this

    mat_free((void**)img->colors);
    img->colors = NULL;
}

image convert_to_image(const bmp* const bmp)
{
    image img;

    // TODO: Implement this
    img.width = bmp->dib_header.width;
    img.height = bmp->dib_header.height;
    img.colors = (rgb**)mat_init(img.height, img.width, sizeof(rgb));

    const unsigned shiftR = 32 - clz(bmp->dib_header.red_bitmask    >> 8);
    const unsigned shiftG = 32 - clz(bmp->dib_header.green_bitmask  >> 8);
    const unsigned shiftB = 32 - clz(bmp->dib_header.blue_bitmask   >> 8);

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
    image copy;

    // TODO: Implement this
    copy.width = img->width;
    copy.height = img->height;
    copy.colors = (rgb**)mat_init(copy.height, copy.width, sizeof(rgb));

    for (int y = 0; y < copy.height; y++) {
        for (int x = 0; x < copy.width; x++) {
            copy.colors[y][x] = img->colors[y][x];
        }
    }

    return copy;
}

void grayscale_image(image* img)
{
    // TODO: Implement this
    for (int y = 0; y < img->height; y++) {
        for (int x = 0; x < img->width; x++) {
            img->colors[y][x].r = (img->colors[y][x].r + img->colors[y][x].g + img->colors[y][x].b) / 3;
            img->colors[y][x].g = img->colors[y][x].r;
            img->colors[y][x].b = img->colors[y][x].r;
        }
    }
}

void apply_filter(image* dst, image* src, unsigned kernel_size, const float* kernel)
{
    // Kernel size must be impair!
    assert(kernel_size % 2 == 1);
    vec2* neighbours = calc_neighbours(kernel_size);

    // TODO : Finish this implementation
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
    // TODO: Implement this
    
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
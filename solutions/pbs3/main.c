#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "matrix.h"
#include "bmp_loader.h"
#include "image.h"

int main()
{
    FILE* fp = fopen("tux.bmp", "rb");

    bmp bmp;
    bmp_load(&bmp, fp);
    bmp_print_info(&bmp);

    fclose(fp);

    image img = convert_to_image(&bmp);
    // grayscale_image(&img);
    image ping = copy_image(&img);
    image pong = copy_image(&img);

    float blur[] = { 
        1, 4, 7, 4, 1,
        4, 16, 26, 16, 4,
        7, 26, 41, 26, 7,
        4, 16, 26, 16, 4,
        1, 4, 7, 4, 1
    };

    for (int i = 0; i < 5*5; i++)
        blur[i] *= 1.f/273.f;

    float sharpen[] = { 
        0.f, -1.f, 0.f
        -1.f, 5.f, -1.f,
        0.f, -1.f, 0.f
    };

    float emboss[] = { 
        -2.f, -1.f, 0.f,
        -1.f, 1, 1.f,
        0.f, 1.f, 2.f
    };

    float outline[] = { 
        -1.f, -1.f, -1.f,
        -1.f,  9.f, -1.f,
        -1.f, -1.f, -1.f
    };

    float edge[] = { 
        1, 0, -1, 
        0, 0, 0,
        -1, 0, 1
    };
    
    for (int i = 0; i < 1; i++) {
        image* src = (i % 2) ? &ping : &pong;
        image* dst = (i % 2) ? &pong : &ping;
        apply_filter(src, dst, 3, edge);
    }

    save_raw(&img, "original.raw");
    save_raw(&pong, "filtered.raw");
}
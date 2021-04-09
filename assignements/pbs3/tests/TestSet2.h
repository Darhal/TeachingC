#pragma once

#include "common.h"
#include "data/pixel.data"
#include "../bmp_loader.h"

/**
 * Tests bmp header loading
 */ 
static void Set2_TestCase1()
{
    FILE* fp = fopen("tux.bmp", "rb");
    bmp_header header;
    bmp_load_header(&header, fp);
    fclose(fp);

    assert(header.signature[0] == 'B'  && RED("\tTest Case #1 : FAILED (Wrong signature)") );
    assert(header.signature[1] == 'M'  && RED("\tTest Case #1 : FAILED (Wrong signature)") );
    assert(header.file_size == 1638538 && RED("\tTest Case #1 : FAILED (Wrong file size)") );
    assert(header.offset_pixels == 138 && RED("\tTest Case #1 : FAILED (Wrong offset to pixels)") );

    puts(GREEN("\tTest Case #1 : PASSED"));
}

/**
 * Tests bmp dib header loading
 */ 
static void Set2_TestCase2()
{
    FILE* fp = fopen("tux.bmp", "rb");
    bmp_header header;
    bmp_load_header(&header, fp);
    bmp_dib_header dib;
    bmp_load_dib_header(&dib, fp);
    fclose(fp);

    assert(dib.header_size == 124           && RED("\tTest Case #2 : FAILED (Wrong dib header size)") );
    assert(dib.width == 640                 && RED("\tTest Case #2 : FAILED (Wrong image width)") );
    assert(dib.height == 640                && RED("\tTest Case #2 : FAILED (Wrong image height)") );
    assert(dib.planes == 1                  && RED("\tTest Case #2 : FAILED (Wrong number of planes)") );
    assert(dib.bpp == 32                    && RED("\tTest Case #2 : FAILED (Wrong bits per pixel)") );
    assert(dib.red_bitmask == 16711680      && RED("\tTest Case #2 : FAILED (Wrong red bitmask)") );
    assert(dib.green_bitmask == 65280       && RED("\tTest Case #2 : FAILED (Wrong green bitmask)") );
    assert(dib.blue_bitmask == 255          && RED("\tTest Case #2 : FAILED (Wrong blue bitmask)") );
    assert(dib.alpha_bitmask == 4278190080  && RED("\tTest Case #2 : FAILED (Wrong alpha bitmask)") );

    puts(GREEN("\tTest Case #2 : PASSED"));
}

/**
 * Tests bmp loading + pixel data reading
 */ 
static void Set2_TestCase3()
{
    bmp b;
    bmp_load(&b, "tux.bmp");

    for (int y = b.dib_header.height - 1; y >= 0; y--) {
        for (int x = 0; x < b.dib_header.width; x++) {
            if (b.pixels[y][x] != tux_data[y][x]) {
                printf(RED("\tTest Case #3 : FAILED (Wrong pixel data at (%u, %u))\n"), y, x);
                assert(0);
            }
        }
    }

    bmp_destroy(&b);
    puts(GREEN("\tTest Case #3 : PASSED"));
}

static void TesetSet2()
{
    printf("Test Set #2 : \n");
    Set2_TestCase1();
    Set2_TestCase2();
    Set2_TestCase3();
    puts(GREEN("\tTest Set #2  : PASSED"));
}
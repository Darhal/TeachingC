#pragma once

#include "common.h"
#include "data/pixel.data"
#include "../bmp_loader.h"

static void TestCase1()
{
    FILE* fp = fopen("../tux.bmp", "rb");
    bmp_header header;
    bmp_load_header(header, fp);
    fclose(fp);

    assert(header.signature[0] == 'B'  && RED("\tTest Case #1 : FAILED (Wrong signature)") );
    assert(header.signature[1] == 'M'  && RED("\tTest Case #1 : FAILED (Wrong signature)") );
    assert(header.file_size == 1638538 && RED("\tTest Case #1 : FAILED (Wrong file size)") );
    assert(header.offset_pixels == 138 && RED("\tTest Case #1 : FAILED (Wrong offset to pixels)") );

    puts(GREEN("\tTest Case #1 : PASSED"));
}

static void TestCase2()
{
    FILE* fp = fopen("../tux.bmp", "rb");
    bmp_header header;
    bmp_load_header(header, fp);
    bmp_dib_header dib;
    bmp_load_dib_header(&dib, fp);
    fclose(fp);

    assert(dib.header_size == 124           && RED("\tTest Case #2 : FAILED (Wrong dib header size)") );
    assert(dib.width == 600                 && RED("\tTest Case #2 : FAILED (Wrong image width)") );
    assert(dib.height == 600                && RED("\tTest Case #2 : FAILED (Wrong image height)") );
    assert(dib.planes == 1                  && RED("\tTest Case #2 : FAILED (Wrong number of planes)") );
    assert(dib.bpp == 32                    && RED("\tTest Case #2 : FAILED (Wrong bits per pixel)") );
    assert(dib.red_bitmask == 16711680      && RED("\tTest Case #2 : FAILED (Wrong red bitmask)") );
    assert(dib.green_bitmask == 65280       && RED("\tTest Case #2 : FAILED (Wrong green bitmask)") );
    assert(dib.blue_bitmask == 255          && RED("\tTest Case #2 : FAILED (Wrong blue bitmask)") );
    assert(dib.alpha_bitmask == 4278190080  && RED("\tTest Case #2 : FAILED (Wrong alpha bitmask)") );

    puts(GREEN("\tTest Case #2 : PASSED"));
}

static void TestCase3()
{
    bmp b;
    bmp_load(&bmp, "../tux.bmp", "rb");

    for (int y = bmp->dib_header.height - 1; y >= 0; y--) {
        for (int x = 0; x < bmp->dib_header.width; x++) {
            assert(bmp->pixels[y][x] == tux_data[y][x]  && RED("\tTest Case #3 : FAILED (Wrong pixel data)") );
        }
    }

    puts(GREEN("\tTest Case #3 : PASSED"));
}

static void TesetSet2()
{
    printf("Test Set #2 : \n");
    TestCase1();
    TestCase2();
    TestCase3();
    puts(GREEN("\tTest Set #2 : PASSED"));
}
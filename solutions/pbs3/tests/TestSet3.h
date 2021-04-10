#pragma once

#include "common.h"
#include "../image.h"
#include "../bmp_loader.h"
#include "data/rgb.data"
#include "data/rgb_filter_edge.data"

/**
 * Test images initialisation
 */
static void Set3_TestCase1()
{
    image img = init_image(100, 100);
    assert(img.width == 100                 && RED("\tTest Case #1 : FAILED (Wrong image width)") );
    assert(img.height == 100                && RED("\tTest Case #1 : FAILED (Wrong image height)") );
    assert(img.colors != NULL               && RED("\tTest Case #1 : FAILED (Pixels matrix should be allocated)") );
    destroy_image(&img);
    puts(GREEN("\tTest Case #1 : PASSED"));
}

/**
 * Test bmp to image conversion (convert_to_image function)
 */ 
static void Set3_TestCase2()
{
    bmp b;
    bmp_load(&b, "tux.bmp");
    image img = convert_to_image(&b);

    assert(img.width  == 640                && RED("\tTest Case #2 : FAILED (Wrong image width)") );
    assert(img.height == 640                && RED("\tTest Case #2 : FAILED (Wrong image height)") );
    assert(img.colors != NULL               && RED("\tTest Case #2 : FAILED (Pixels matrix should be allocated)") );

    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            int invalid = img.colors[y][x].r != tux_rgb_data[y][x].r || img.colors[y][x].g != tux_rgb_data[y][x].g || img.colors[y][x].b != tux_rgb_data[y][x].b;

            if (invalid) {
                printf(RED("\tTest Case #2 : FAILED (Wrong RGB pixel data at (%u, %u))\n"), y, x);
                fflush(stdout);
                assert(0);
            }
        }
    }

    bmp_destroy(&b);
    destroy_image(&img);
    puts(GREEN("\tTest Case #2 : PASSED"));
}

/**
 * Test image copying (copy_image function)
 */ 
static void Set3_TestCase3()
{
    bmp b;
    bmp_load(&b, "tux.bmp");
    image img = convert_to_image(&b);
    image img2 = copy_image(&img);

    assert(img.width  == img2.width                && RED("\tTest Case #3 : FAILED (Wrong image width)") );
    assert(img.height == img2.height               && RED("\tTest Case #3 : FAILED (Wrong image height)") );
    assert(img.colors != img2.colors               && RED("\tTest Case #3 : FAILED (Images shouldn't share the pixels matrix)") );

    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            int invalid = img.colors[y][x].r != img2.colors[y][x].r || img.colors[y][x].g != img2.colors[y][x].g || img.colors[y][x].b != img2.colors[y][x].b;

            if (invalid) {
                printf(RED("\tTest Case #3 : FAILED (Wrong RGB pixel data at (%u, %u))\n"), y, x);
                fflush(stdout);
                assert(0);
            }
        }
    }

    bmp_destroy(&b);
    destroy_image(&img);
    destroy_image(&img2);
    puts(GREEN("\tTest Case #3 : PASSED"));
}

/**
 * Test image grayscaling (grayscale_image function)
 */ 
static void Set3_TestCase4()
{
    bmp b;
    bmp_load(&b, "tux.bmp");
    image img = convert_to_image(&b);
    image img2 = copy_image(&img);
    grayscale_image(&img2);

    assert(img.width  == img2.width                && RED("\tTest Case #4 : FAILED (Wrong image width)") );
    assert(img.height == img2.height               && RED("\tTest Case #4 : FAILED (Wrong image height)") );
    assert(img.colors != img2.colors               && RED("\tTest Case #4 : FAILED (Images shouldn't share the pixels matrix)") );

    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            int average = (img.colors[y][x].r + img.colors[y][x].g + img.colors[y][x].b) / 3;
            int invalid = img2.colors[y][x].r != average || img2.colors[y][x].g != average || img2.colors[y][x].b != average;

            if (invalid) {
                printf(RED("\tTest Case #4 : FAILED (Wrong RGB pixel data at (%u, %u))\n"), y, x);
                fflush(stdout);
                assert(0);
            }
        }
    }

    bmp_destroy(&b);
    destroy_image(&img);
    destroy_image(&img2);
    puts(GREEN("\tTest Case #4 : PASSED"));
}

/**
 * Test convolution products on images (apply_filter function)
 */ 
static void Set3_TestCase5()
{
    const char tolerance = 10;
    const float edge_kernel[] = { 
        1, 0, -1, 
        0, 0, 0,
        -1, 0, 1
    };

    bmp b;
    bmp_load(&b, "tux.bmp");
    image src = convert_to_image(&b);
    image dst = init_image(src.width, src.height);
    apply_filter(&dst, &src, 3, edge_kernel);

    assert(src.width  == dst.width                && RED("\tTest Case #5 : FAILED (Wrong image width)") );
    assert(src.height == dst.height               && RED("\tTest Case #5 : FAILED (Wrong image height)") );
    assert(src.colors != dst.colors               && RED("\tTest Case #5 : FAILED (Images shouldn't share the pixels matrix)") );

    for (int y = 0; y < src.height; y++) {
        for (int x = 0; x < src.width; x++) {
            int invalid = abs(dst.colors[y][x].r - tux_filter_edge[y][x].r) > tolerance ||
                          abs(dst.colors[y][x].g - tux_filter_edge[y][x].g) > tolerance ||
                          abs(dst.colors[y][x].b - tux_filter_edge[y][x].b) > tolerance;

            if (invalid) {
                printf(RED("\tTest Case #5 : FAILED (Wrong RGB pixel data at (%u, %u))\n"), y, x);
                fflush(stdout);
                assert(0);
            }
        }
    }

    bmp_destroy(&b);
    destroy_image(&src);
    destroy_image(&dst);
    puts(GREEN("\tTest Case #5 : PASSED"));
}

/**
 * Test saving images to disk (save_raw function)
 */ 
static void Set3_TestCase6()
{
    const float edge_kernel[] = { 
        1, 0, -1, 
        0, 0, 0,
        -1, 0, 1
    };

    bmp b;
    bmp_load(&b, "tux.bmp");
    image src = convert_to_image(&b);
    image dst = init_image(src.width, src.height);
    apply_filter(&dst, &src, 3, edge_kernel);
    save_raw(&dst, "filtered.raw");

    assert(src.width  == dst.width                && RED("\tTest Case #6 : FAILED (Wrong image width)") );
    assert(src.height == dst.height               && RED("\tTest Case #6 : FAILED (Wrong image height)") );
    assert(src.colors != dst.colors               && RED("\tTest Case #6 : FAILED (Images shouldn't share the pixels matrix)") );
    FILE* fp = fopen("filtered.raw", "rb");

    for (int y = 0; y < dst.height; y++) {
        for (int x = 0; x < dst.width; x++) {
            unsigned char r, g, b, a;
            (void)fread(&b, sizeof(unsigned char), 1, fp);
            (void)fread(&g, sizeof(unsigned char), 1, fp);
            (void)fread(&r, sizeof(unsigned char), 1, fp);
            (void)fread(&a, sizeof(unsigned char), 1, fp);
            int invalid = dst.colors[y][x].r != r || dst.colors[y][x].g != g || dst.colors[y][x].b != b;

            if (invalid) {
                printf(RED("\tTest Case #6 : FAILED (Wrong RGB pixel data at (%u, %u)) did you save the raw file in BGRA format ?\n"), y, x);
                fflush(stdout);
                assert(0);
            }
        }
    }

    bmp_destroy(&b);
    destroy_image(&src);
    destroy_image(&dst);
    puts(GREEN("\tTest Case #6 : PASSED"));
}

static void TesetSet3()
{
    printf("Test Set #3 : \n");
    Set3_TestCase1();
    Set3_TestCase2();
    Set3_TestCase3();
    Set3_TestCase4();
    Set3_TestCase5();
    Set3_TestCase6();
    puts(GREEN("\tTest Set #3  : PASSED"));
}
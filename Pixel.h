//
// Created by wil98 on 2017-06-13.
//

#ifndef PPM_PIXEL_H
#define PPM_PIXEL_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "Macro.h"

enum ImageType {BINARY, COLOR};

/* Pixel */
typedef struct Pixel {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} Pixel;

/* Image */
typedef struct Image {
    unsigned int size;
    unsigned int width;
    unsigned int height;
    int mode;
    unsigned int maxColor;
    Pixel**pixels;
} Image;

/*
 * Allocate a pixel
 */
Pixel*createPixel(unsigned char r, unsigned char g, unsigned char b);
/*
 * Allocate an image
 */
Image* createImage(unsigned int W, unsigned int H, int mode, unsigned int maxColor);
/*
 * Delete an image
 */
void deleteImage(Image* image);
/*
 * Return the pixel at (x, y)
 */
Pixel*getPixelInImage(Image* image, int x, int y);
/*
 * Set the color of the pixel at (x, y)
 */
void setPixelColor(Image* image, int x, int y, unsigned char r, unsigned char g, unsigned char b);
/*
 * Set "color" of pixel for binary image
 * Equivalent to (setPixelColor(image, x, y, c, c, c);)
 */
void setPixelBinary(Image* image, int x, int y, unsigned char c);
/*
 * Write the image in PPM format to disk
 */
void writeImageToFile(FILE* file, Image* image);

#endif //PPM_PIXEL_H

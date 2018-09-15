//
// Created by wil98 on 2017-06-13.
//
#include "Pixel.h"

Pixel*createPixel(unsigned char r, unsigned char g, unsigned char b)
{
    Pixel*pixel = (Pixel*)malloc(sizeof(Pixel));
    if (!pixel)
        return NULL;
    pixel->r = r;
    pixel->g = g;
    pixel->b = b;
    return pixel;
}

Image* createImage(unsigned int W, unsigned int H, int mode, unsigned int maxColor)
{
    Image*image = (Image*)malloc(sizeof(Image));
    if (!image)
        return NULL;
    image->size = W*H;
    image->width = W;
    image->height = H;
    image->mode = mode;
    image->maxColor = maxColor;
    image->pixels = malloc(image->size * sizeof(Pixel*));
    if (!image->pixels)
        return NULL;
    for (int i = 0; i < image->size; ++i)
    {
        image->pixels[i] = createPixel(0, 0, 0);
    }
    return image;
}

void deleteImage(Image* image)
{
    if (image)
        if (image->pixels)
            if (image->pixels)
                for (int i = 0; i <image->size; ++i)
                    free(image->pixels[i]);
}

Pixel*getPixelInImage(Image* image, int x, int y)
{
    return image->pixels[x + y * image->width];
}

void setPixelColor(Image* image, int x, int y, unsigned char r, unsigned char g, unsigned char b)
{
    if (x > 0 && x < image->width && y > 0 && y < image->height)
    {
        Pixel *pixel = image->pixels[x + y * image->width];
        pixel->r = r;
        pixel->g = g;
        pixel->b = b;
    }
}

void setPixelBinary(Image* image, int x, int y, unsigned char c)
{
    setPixelColor(image, x, y, c, c, c);
}

void writeImageToFile(FILE* file, Image* image)
{
    if (file && image)
    {
        char buffer[1000];
        /* HEADER */
        if (image->mode == BINARY)
        {
            strcpy(buffer, "P1\n\0");
        }
        else if (image->mode == COLOR)
        {
            strcpy(buffer, "P3\n\0");
        };
        WRITE_TO_FILE(buffer, file);

        /* SIZE */
        sprintf(buffer, "%i %i\n\0", image->width, image->height);
        WRITE_TO_FILE(buffer, file);

        /* MAX2 COLOR */
        if (image->maxColor > 1)
        {
            sprintf(buffer, "%i\n\0", image->maxColor);
            WRITE_TO_FILE(buffer, file);
        }

        /* DATA */
        for (int y = 0; y < image->height; ++y)
        {
            for (int x = 0; x < image->width ; ++x)
            {
                Pixel* pixel = getPixelInImage(image, x, y);
                if (image->mode == BINARY)
                {
                    sprintf(buffer, "%i ", pixel->r);
                }
                else if (image->mode == COLOR)
                {
                    sprintf(buffer, "%i %i %i ", pixel->r, pixel->g, pixel->b);
                }

                WRITE_TO_FILE(buffer, file);
            }
            WRITE_TO_FILE("\n", file);
        }
    }
}

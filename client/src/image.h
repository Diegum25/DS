#ifndef DS_IMAGE_H
#define DS_IMAGE_H

#include "pixel.h"
#include <stdint.h>

typedef struct{
    Pixel* image;
    uint16_t width, height;
} Image;

Image* DS_CreateImage(uint16_t width, uint16_t height);
void DS_DeleteImage(Image* image);
void DS_WriteImage(Image* image, const char* filename);

#endif
#ifndef DS_IMAGE_H
#define DS_IMAGE_H

#include "pixel.h"

typedef struct{
    Pixel* image;
    Uint16 width, height;
} Image;

Image* DS_CreateImage(Uint16 width, Uint16 height);
void DS_DestroyImage(Image* image);
void DS_WriteImage(Image* image, const char* filename);

#endif
#include "image.h"
#include "pixel.h"
#include <stdlib.h>

#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
    #define STB_IMAGE_WRITE_IMPLEMENTATION
#endif

#include "stb_image_write.h"

Image* DS_CreateImage(uint16_t width, uint16_t height){
    Image* image = malloc(sizeof(Image));
    image->width = width;
    image->height = height;
    image->image = calloc(width*height, sizeof(Pixel));
    return image;
};

void DS_DeleteImage(Image* image){
    free(image->image);
    free(image);
};

void DS_WriteImage(Image* image, const char* filename){
    stbi_write_png("build/rays.png",image->width,image->height,4,image->image,sizeof(Pixel)*image->width);
};
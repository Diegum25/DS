#include <sys/types.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "pixel.h"
#include <stdlib.h>

int main(){
    int x = 256, y = 256;

    Pixel* pixels = calloc(y*x, sizeof(Pixel));

    for (int i = 0; i < x ; i++){
        for (int j = 0; j < y ; j++){
            pixels[i+(x*j)] = DS_CreatePixel(i, j, 0, 255);
        }
    }

    // :)
    pixels[0].g = 255;
    pixels[3].g = 255;
    pixels[0+(x*2)].g = 255;
    pixels[1+(x*3)].g = 255;
    pixels[2+(x*3)].g = 255;
    pixels[3+(x*2)].g = 255;

    stbi_write_png("build/:).png",x,y,4,pixels,sizeof(Pixel)*x);
    return 0;
}
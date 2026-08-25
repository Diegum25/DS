#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "pixel.h"
#include <stdlib.h>

#define COLOR 0xFF00FF00;

int main(){
    int x = 256, y = 256;

    Pixel* pixels = calloc(y*x, sizeof(Pixel));

    // :)

    // like this
    for (int i = 0; i < x ; i++){
        for (int j = 0; j < y ; j++){
            DS_SetRGBA(&pixels[i+(x*j)].pixel_t,i,j,0,255);
        }
    }

    // like that
    pixels[0].pixel_t = COLOR;

    // like this this
    DS_SetRGBA((pixel_t*)&pixels[3], 0, 255, 0, 255);

    // like that
    pixels[0+(x*2)].pixel_s.g = 255;
    pixels[1+(x*3)].pixel_s.g = 255;
    pixels[2+(x*3)].pixel_s.g = 255;
    pixels[3+(x*2)].pixel_s.g = 255;

    stbi_write_png("build/:).png",x,y,4,pixels,sizeof(pixel_t)*x);
    return 0;
}
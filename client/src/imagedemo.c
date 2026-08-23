#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "pixel.h"
#include <stdlib.h>

#define COLOR 0xFF00FF00;

int main(){
    int x = 16, y = 16;

    Pixel* pixels = calloc(y*x, sizeof(Pixel));

    // :)

    // like this
    for (int i = 0; i < x*y ; i++){
        DS_SetRGBA(&pixels[i], 255, 255, 255, 255);
    }

    // like that
    pixels[0] = COLOR;
    pixels[3] = COLOR;

    pixels[0+(x*2)] = COLOR;
    pixels[1+(x*3)] = COLOR;
    pixels[2+(x*3)] = COLOR;
    pixels[3+(x*2)] = COLOR;

    stbi_write_png("build/:).png",x,y,4,pixels,sizeof(Pixel)*x);
    return 0;
}
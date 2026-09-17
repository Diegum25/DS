#ifndef DS_UTIL_H
#define DS_UTIL_H

#include <SDL3/SDL_stdinc.h>

typedef Uint32 pixel_t;

typedef union{
    pixel_t pixel_t;
    struct{
        Uint8 r,g,b,a;
    };
}Pixel;

Pixel DS_CreatePixel(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

#endif
#ifndef DS_UTIL_H
#define DS_UTIL_H

#include <sys/types.h>

typedef u_int32_t pixel_t;

typedef union{
    pixel_t pixel_t;
    struct{
        u_int8_t r,g,b,a;
    };
}Pixel;

Pixel DS_CreatePixel(u_int8_t r, u_int8_t g, u_int8_t b, u_int8_t a);

#endif
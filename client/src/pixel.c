#include "pixel.h"
#include <sys/types.h>

Pixel DS_CreatePixel(u_int8_t r, u_int8_t g, u_int8_t b, u_int8_t a){
    Pixel ret = {.r = r, .g = g, .b = b, .a = a};
    return ret;
};
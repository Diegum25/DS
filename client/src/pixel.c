#include "pixel.h"
#include <sys/types.h>

void DS_StripA(Pixel* pixel){
    *pixel = *pixel | 0xFF000000;
};

void DS_SetR(Pixel* pixel, u_int8_t value){
    u_int32_t shifted = value; // no shift
    u_int32_t zeros = *pixel & 0xFFFFFF00;
    *pixel = zeros | shifted;
};

void DS_SetG(Pixel* pixel, u_int8_t value){
    u_int32_t shifted = ((u_int32_t)value) << 8;
    u_int32_t zeros = *pixel & 0xFFFF00FF;
    *pixel = zeros | shifted;
};

void DS_SetB(Pixel* pixel, u_int8_t value){
    u_int32_t shifted = ((u_int32_t)value) << 8*2;
    u_int32_t zeros = *pixel & 0xFF00FFFF;
    *pixel = zeros | shifted;
};

void DS_SetA(Pixel* pixel, u_int8_t value){
    u_int32_t shifted = ((u_int32_t)value) << 8*3;
    u_int32_t zeros = *pixel & 0x00FFFFFF;
    *pixel = zeros | shifted;
};

void DS_SetRGBA(Pixel* pixel, u_int8_t r, u_int8_t g, u_int8_t b, u_int8_t a){
    u_int32_t r_shifted = r;
    u_int32_t g_shifted = ((u_int32_t)g) << 8;
    u_int32_t b_shifted = ((u_int32_t)b) << 8*2;
    u_int32_t a_shifted = ((u_int32_t)a) << 8*3;
    *pixel = r_shifted | g_shifted | b_shifted | a_shifted;
};

u_int8_t DS_GetR(Pixel* pixel){
    return (*pixel & 0x000000FF);
};

u_int8_t DS_GetG(Pixel* pixel){
    return (*pixel & 0x0000FF00) >> 8;
};

u_int8_t DS_GetB(Pixel* pixel){
    return (*pixel & 0x00FF0000) >> 8*2;
};

u_int8_t DS_GetA(Pixel* pixel){
    return (*pixel & 0xFF000000) >> 8*3;
};

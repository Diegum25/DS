#ifndef DS_UTIL_H
#define DS_UTIL_H

#include <sys/types.h>

typedef u_int32_t pixel_t;

typedef struct{
    u_int8_t r;
    u_int8_t g;
    u_int8_t b;
    u_int8_t a;
}pixel_s;

typedef union{
    pixel_t pixel_t;
    pixel_s pixel_s;
}Pixel;

void DS_StripA(pixel_t*);

void DS_SetA(pixel_t*,u_int8_t);
void DS_SetR(pixel_t*,u_int8_t);
void DS_SetG(pixel_t*,u_int8_t);
void DS_SetB(pixel_t*,u_int8_t);

void DS_SetRGBA(pixel_t*, u_int8_t r, u_int8_t g, u_int8_t b, u_int8_t a);

u_int8_t DS_GetA(pixel_t*);
u_int8_t DS_GetR(pixel_t*);
u_int8_t DS_GetG(pixel_t*);
u_int8_t DS_GetB(pixel_t*);

#endif
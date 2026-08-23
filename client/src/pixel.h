#ifndef DS_UTIL_H
#define DS_UTIL_H

#include <sys/types.h>

typedef u_int32_t Pixel;

void DS_StripA(Pixel*);

void DS_SetA(Pixel*,u_int8_t);
void DS_SetR(Pixel*,u_int8_t);
void DS_SetG(Pixel*,u_int8_t);
void DS_SetB(Pixel*,u_int8_t);

void DS_SetRGBA(Pixel*, u_int8_t r, u_int8_t g, u_int8_t b, u_int8_t a);

u_int8_t DS_GetA(Pixel*);
u_int8_t DS_GetR(Pixel*);
u_int8_t DS_GetG(Pixel*);
u_int8_t DS_GetB(Pixel*);

#endif
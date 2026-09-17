#ifndef DS_RAYUTIL_H
#define DS_RAYUTIL_H

#include "image.h"
#include "pixel.h"
#include "ray.h"
#include "hittable.h"
#include <sys/types.h>

Pixel DS_RayColor(Ray* ray, Hittable* hittable);

typedef struct{
    Ray ray;
    Hittable* hittable;
    Image* image;
    u_int16_t x,y;
}RayData;

#endif
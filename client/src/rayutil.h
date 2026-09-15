#ifndef DS_RAYUTIL_H
#define DS_RAYUTIL_H

#include "pixel.h"
#include "ray.h"
#include "hittable.h"

Pixel DS_RayColor(Ray* ray, Hittable* hittable);

#endif
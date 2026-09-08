#ifndef DS_RAY_H
#define DS_RAY_H

#include "cglm/types.h"
#include "pixel.h"

typedef struct{
    vec3 origin;
    vec3 destination;
}Ray;

Ray DS_CreateRay(vec3 origin, vec3 destination);
void DS_RayAt(Ray ray, float t, vec3 dest);
Pixel DS_RayColor(Ray ray);

#endif
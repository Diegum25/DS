#ifndef DS_SPHERE_H
#define DS_SPHERE_H

#include "hittable.h"

typedef struct Sphere{
    Hittable super;
    vec3 origin;
    float radius;
}Sphere;

Sphere* DS_CreateSphere(vec3 position, float radius);
void DS_DestroySphere(Sphere* sphere);

#endif
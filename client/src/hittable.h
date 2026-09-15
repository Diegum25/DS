#ifndef DS_HITTABLE_H
#define DS_HITTABLE_H

#include "cglm/types.h"
#include "stdbool.h"
#include "ray.h"

typedef struct {
    vec3 p;
    vec3 normal;
    float t;
}HitRecord;

typedef struct Hittable{
    bool (*hit)(struct Hittable* this, Ray* ray, float ray_tmin, float ray_tmax, HitRecord* hitRecord);
}Hittable;

#endif
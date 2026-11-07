#ifndef DS_HITTABLE_H
#define DS_HITTABLE_H

#include "cglm/types.h"
#include "stdbool.h"
#include "ray.h"

typedef struct {
    vec3 p;
    vec3 normal;
    float t;
    bool frontFaced;
}HitData;

typedef struct Hittable{
    bool (*hit)(struct Hittable* this, Ray* ray, float ray_tmin, float ray_tmax, HitData* hitRecord);
}Hittable;

void HitDataFaceNormal(HitData* hr, Ray* ray, vec3 outNormal);

#endif
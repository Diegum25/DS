#include "ray.h"
#include "cglm/types.h"
#include "cglm/vec3.h"
#include <float.h>
#include <stdbool.h>
#include "pixel.h"
#include "hittable.h"

Ray DS_CreateRay(float *origin, float *destination){
    Ray ray = {0};
    glm_vec3_copy(origin, ray.origin);
    glm_vec3_copy(destination, ray.destination);
    return ray;
};

void DS_RayAt(Ray* ray, float t, vec3 dest){
    vec3 mul;
    glm_vec3_scale(ray->destination, t, mul);
    glm_vec3_add(ray->origin, mul, dest);
};

Pixel DS_RayColor(Ray* ray, Hittable* hittable){
    HitRecord record;
    if(hittable->hit(hittable,ray,0,FLT_MAX,&record)){
        vec3 color = {0};
        vec3 add = {1,1,1};
        glm_vec3_add(record.normal, add, color);
        glm_vec3_scale(color, 0.5f*255, color);
        Pixel pixel = {.a = 255, .r = color[0], .g = color[1], .b = color[2]};
        return pixel;
    }
    vec3 normalized = {0}; glm_vec3_copy(ray->destination,normalized);
    glm_vec3_normalize(normalized);
    vec3 white = {1,1,1};
    vec3 blue = {0.5,0.5,1};
    vec3 color = {0};
    glm_vec3_lerpc(white,blue,normalized[1],color);
    Pixel pixel = {.a = 255, .r = color[0]*255, .g = color[1]*255, .b = color[2]*255};
    return pixel;
};
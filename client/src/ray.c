#include "ray.h"
#include "cglm/types.h"
#include "cglm/vec3.h"
#include <float.h>
#include <stdbool.h>
#include "pixel.h"
#include "hittable.h"

Ray DS_CreateRay(vec3 origin, vec3 destination){
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

void RayNormalColor(Ray* ray, vec3 dest){
    /* vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0); */
    vec3 normalized = {0};
    glm_vec3_copy(ray->destination,normalized);
    glm_vec3_normalize(normalized);
    vec3 white = {1,1,1};
    vec3 blue = {0.5,0.5,1};
    glm_vec3_lerpc(white,blue,normalized[1],dest);
};

void RayColor(Ray* ray, Hittable* list, Uint8 remaining, vec3 dest){
    vec3 color = {0};
    RayNormalColor(ray, color);
    if(remaining > 0){
        HitData data = {0};
        if(list->hit(list,ray,0,FLT_MAX,&data)){
            vec3 ret = {0};
            vec3 dir = {0};
            glm_vec3_reflect(ray->destination, data.normal, dir);
            Ray newRay = DS_CreateRay(data.p, dir); // <- correct?
            RayColor(&newRay, list, remaining - 1, ret);
            vec3 mult = {0.5f,0.5f,0.5f};
            glm_vec3_mul(ret, mult, color);
        }
    }
    glm_vec3_copy(color, dest);
};

Pixel DS_RayColor(Ray* ray, Hittable* hittable, Uint8 bounces){
    vec3 color = {0};
    RayColor(ray, hittable, bounces, color);
    Pixel pixel = {.a = 255, .r = color[0]*255, .g = color[1]*255, .b = color[2]*255};
    return pixel;
};
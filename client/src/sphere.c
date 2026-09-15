#include "hittable.h"
#include "cglm/vec3.h"
#include "ray.h"
#include <stdlib.h>
#include "sphere.h"

bool SphereHit(Hittable* this, Ray* ray, float ray_tmin, float ray_tmax, HitRecord* hitRecord){
    Sphere* sphere = (Sphere*)this;
    // wtf
    vec3 oc;
    glm_vec3_sub(sphere->origin,ray->origin,oc);

    float a = ray->destination[0] * ray->destination[0] + ray->destination[1] * ray->destination[1] + ray->destination[2] * ray->destination[2];
    float h = glm_vec3_dot(ray->destination, oc);
    float c = (oc[0] * oc[0] + oc[1] * oc[1] + oc[2] * oc[2]) - sphere->radius * sphere->radius;

    float discrimination = h*h - a*c;

    if(discrimination < 0) return false;

    float sqrtd = sqrtf(discrimination);

    // Find the nearest root that lies in the acceptable range.
    float root = (h - sqrtd) / a;
    if (root <= ray_tmin || ray_tmax <= root) {
        root = (h + sqrtd) / a;
        if (root <= ray_tmin || ray_tmax <= root) return false;
    }

    hitRecord->t = root;
    DS_RayAt(ray, root, hitRecord->p);
    glm_vec3_sub(hitRecord->p, sphere->origin, hitRecord->normal);
    glm_vec3_divs(hitRecord->normal, sphere->radius, hitRecord->normal);

    return true;
};

Sphere* DS_CreateSphere(vec3 position, float radius){
    Sphere* sphere = calloc(1, sizeof(Sphere));
    sphere->super.hit = &SphereHit;
    glm_vec3_copy(position, sphere->origin);
    sphere->radius = radius;
    return sphere;
};

void DS_DestroySphere(Sphere* sphere){
    free(sphere);
};
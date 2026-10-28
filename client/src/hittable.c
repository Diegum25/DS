#include "hittable.h"
#include "cglm/types.h"
#include "cglm/vec3.h"
#include "ray.h"

void HitRecordFaceNormal(HitRecord* hr, Ray* ray, vec3 outNormal){
    float dot = glm_dot(ray->destination, outNormal);
    hr->frontFaced = dot < 0;
    if (hr->frontFaced){
        glm_vec3_copy(outNormal, hr->normal);
    }else{
        vec3 negOutNomral = {0};
        glm_vec3_scale(outNormal, -1.0f, negOutNomral);
        glm_vec3_copy(negOutNomral, hr->normal);
    }
}
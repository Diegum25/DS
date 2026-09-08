#include "camera.h"
#include "cglm/vec3.h"
#include "image.h"
#include "pixel.h"
#include "ray.h"
#include <sys/types.h>

// https://raytracing.github.io/books/RayTracingInOneWeekend.html

int main(){
    u_int16_t x = 800, y = 800;
    
    Image* image = DS_CreateImage(x,y);

    Camera cam = DS_CreateCamera(image);

    for(int i = 0; i < x;i++){
        for(int j = 0; j < y; j++){
            vec3 horizontal = {0}; glm_vec3_scale(cam.viewport.horizontalDelta, i, horizontal);
            vec3 vertical = {0}; glm_vec3_scale(cam.viewport.verticalDelta, j, vertical);

            vec3 pixel = {0};
            glm_vec3_add(cam.zero, horizontal, pixel);
            glm_vec3_add(pixel, vertical, pixel);

            vec3 direction = {0};
            glm_vec3_sub(pixel, cam.position, direction);

            Ray ray = {0};
            glm_vec3_copy(cam.position, ray.origin);
            glm_vec3_copy(direction, ray.destination);

            Pixel color = DS_RayColor(ray);

            image->image[i+(x*j)] = color;
        }
    }

    DS_WriteImage(image, "build/rays.png");

    DS_DeleteImage(image);

    return 0;
};
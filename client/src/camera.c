#include "camera.h"
#include "cglm/types.h"
#include "cglm/vec3.h"

Camera DS_CreateCamera(Image* image){
    Camera cam = {0};
    cam.focalLenght = 1.0f;
    cam.viewport.horizontal[0] = 1.0f;
    cam.viewport.vertical[1] = -1.0f;
    glm_vec3_divs(cam.viewport.horizontal, image->width, cam.viewport.horizontalDelta);
    glm_vec3_divs(cam.viewport.vertical, image->height, cam.viewport.verticalDelta);

    //viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;}
    vec3 focalVector = {0,0,cam.focalLenght};
    vec3 horizontalVecDivBy2 = {0};
    vec3 verticalVecDivBy2 = {0};

    glm_vec3_divs(cam.viewport.horizontal, 2.0f, horizontalVecDivBy2);
    glm_vec3_divs(cam.viewport.vertical, 2.0f, verticalVecDivBy2);

    glm_vec3_sub(cam.position, focalVector, cam.viewportUL);
    glm_vec3_sub(cam.viewportUL, horizontalVecDivBy2, cam.viewportUL);
    glm_vec3_sub(cam.viewportUL, verticalVecDivBy2, cam.viewportUL);

    //pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    vec3 sum;

    glm_vec3_add(cam.viewport.horizontalDelta,cam.viewport.verticalDelta,sum);
    glm_vec3_scale(sum, 0.5f, sum);

    glm_vec3_add(cam.viewportUL,sum,cam.zero);

    return cam;
};
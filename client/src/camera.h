#ifndef DS_CAMERA_H
#define DS_CAMERA_H

#include "cglm/types.h"
#include "image.h"

struct s_viewport {
    vec3 horizontal;
    vec3 vertical;
    vec3 horizontalDelta;
    vec3 verticalDelta;
};

typedef struct{
    vec3 position;
    vec3 up;
    vec3 right;
    float focalLenght;
    struct s_viewport viewport;
    vec3 viewportUL;
    vec3 zero;
}Camera;

Camera DS_CreateCamera(Image* image);

#endif
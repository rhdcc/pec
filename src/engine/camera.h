#ifndef CAMERA_H
#define CAMERA_H

#include "utils/defines.h"
#include <cglm/cglm.h>

typedef struct {
    mat4 projection;
    vec3 position;
} Camera;

Camera camera_create(vec3 position, s32 width, s32 height);
void camera_get_view(Camera *camera, mat4 view);

#endif // CAMERA_H
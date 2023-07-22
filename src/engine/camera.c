#include "engine/camera.h"

Camera camera_create(vec3 position, s32 width, s32 height) {
    Camera cam;
    glm_vec3_copy(position, cam.position);
    glm_ortho(0, (f32)width, (f32)height, 0, -1, 100.0f, cam.projection);
    return cam;
}

void camera_get_view(Camera *camera, mat4 view) {
    glm_mat4_identity(view);
    glm_translate(view, camera->position);
}

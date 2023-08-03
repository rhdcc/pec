#include "engine/entity.h"

void create_model_transform(mat4 model, Entity *entity) {
    glm_mat4_identity(model);
    glm_translate(model, entity->position);
    vec3 scale = { entity->scale, entity->scale, 1.0f };
    glm_scale(model, scale);
    glm_rotate_x(model, entity->rx, model);
    glm_rotate_y(model, entity->ry, model);
    glm_rotate_z(model, entity->rz, model);
}

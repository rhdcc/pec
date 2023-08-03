#ifndef ENTITY_H
#define ENTITY_H

#include "utils/defines.h"
#include "cglm/cglm.h"
#include "renderer/models.h"

typedef struct {
    RawModel model;
    vec3 position;
    f32 rx, ry, rz, scale;
} Entity;

void create_model_transform(mat4 model, Entity *entity);

#endif // ENTITY_H
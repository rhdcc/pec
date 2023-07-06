#ifndef ENTITY_H
#define ENTITY_H

#include "utils/defines.h"
#include "external/linmath.h"
#include "renderer/models.h"

typedef struct {
    RawModel model;
    vec3 position;
    f32 rx, ry, rz, scale;
} Entity;

#endif // ENTITY_H
#ifndef RENDERER_H
#define RENDERER_H

#include "shaders/shader_program.h"
#include "entities/entity.h"
#include "renderer/models.h"
#include "engine/camera.h"

void renderer_prepare(void);
void render(Entity *e, ShaderProgram *sp, Camera *camera);

#endif // RENDERER_H
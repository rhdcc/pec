#ifndef RENDERER_H
#define RENDERER_H

#include "shaders/shader_program.h"
#include "entities/entity.h"
#include "renderer/models.h"

void renderer_prepare(void);
void render(Entity *e, ShaderProgram *sp);

#endif // RENDERER_H
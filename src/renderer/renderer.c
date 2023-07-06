#include <glad/glad.h>
#include "external/linmath.h"

#include "renderer/renderer.h"

static void mat4_create_transform(mat4x4 out, vec3 t, f32 rx, f32 ry, f32 rz, f32 scale) { // TODO: Move to appropriate file
    mat4x4_translate(out, t[0], t[1], t[2]);
    mat4x4_rotate_X(out, out, rx);
    mat4x4_rotate_Y(out, out, ry);
    mat4x4_rotate_Y(out, out, rz);
    mat4x4_scale(out, out, scale);
}

void renderer_prepare(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void render(Entity *entity, ShaderProgram *sp) {
    glBindVertexArray(entity->model.vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    mat4x4 transform;
    mat4_create_transform(transform,
        entity->position,
        entity->rx, 
        entity->ry, 
        entity->rz, 
        entity->scale);
    set_uniform_m4(sp, "u_transform", transform);
    vec3 color = { 0.0f, 1.0f, 0.0f };
    set_uniform_v3(sp, "u_color", color);

    glDrawElements(GL_TRIANGLES, entity->model.vertex_count, GL_UNSIGNED_INT, (void *)0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindVertexArray(0);
}
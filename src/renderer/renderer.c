#include <glad/glad.h>

#include "renderer/renderer.h"

void renderer_prepare(void) {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void render(Entity *entity, ShaderProgram *sp, Camera *camera) {
    glBindVertexArray(entity->model.vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    set_uniform_m4(sp, "u_projection", camera->projection);
    mat4 view;
    camera_get_view(camera, view);
    set_uniform_m4(sp, "u_view", view);

    mat4 model;
    create_model_transform(model, entity);
    set_uniform_m4(sp, "u_model", model);

    vec3 color = { 0.0f, 1.0f, 0.0f };
    set_uniform_v3(sp, "u_color", color);

    glDrawElements(GL_TRIANGLES, entity->model.vertex_count, GL_UNSIGNED_INT, (void *)0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindVertexArray(0);
}
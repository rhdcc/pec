#include "utils/defines.h"
#include "renderer/display.h"
#include "renderer/loader.h"
#include "renderer/renderer.h"
#include "shaders/shader_program.h"
#include "entities/entity.h"

void static_shader_callback(ShaderProgram *sp) {
    bind_attribute(sp, 0, "a_position");
}

void static_get_all_uniforms(ShaderProgram *sp) {
}

int main(void) {
    display_create(1280, 720);
    Loader loader = {0};
    ShaderProgram static_program = create_shader_program(
        "res/shaders/vertex.glsl",
        "res/shaders/fragment.glsl",
        static_shader_callback,
        static_get_all_uniforms);

    f32 vertices[] = {
        -0.5f, +0.5f, +0.0f,
        -0.5f, -0.5f, +0.0f,
        +0.5f, -0.5f, +0.0f,
        +0.5f, +0.5f, +0.0f
    };
    u32 indices[] = {
        0, 1, 2, 2, 3, 0
    };
    RawModel model = load_to_vao(&loader,
        indices, sizeof(indices)/sizeof(indices[0]),
        vertices, sizeof(vertices)/sizeof(vertices[0]));
    Entity e = {
        .model = model,
        .rx = 0.f, .ry = 0.f, .rz = 0.f, .scale = 1.f
    };
    e.position[0] = 0;
    e.position[1] = 0;
    e.position[2] = 0;
    
    while(!display_should_close()) {
        renderer_prepare();
        shader_program_start(&static_program);
        render(&e, &static_program);
        shader_program_stop(&static_program);
        // Game logic
        // e.position[0] += 0.0001f;
        display_update();
    }

    shader_program_cleanup(&static_program);
    loader_cleanup(&loader);
    display_close();
}
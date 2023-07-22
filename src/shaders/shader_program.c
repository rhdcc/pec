#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include "utils/log.h"

#include "shaders/shader_program.h"

static char *slurp_file(const char *path) {
    FILE *file = fopen(path, "rb");
    if(!file) {
        LOG_ERROR("Failed to open file \"%s\".\n", path);
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *buffer = malloc(length + 1);
    if(!buffer) {
        LOG_ERROR("Failed to allocate buffer for file \"%s\".\n", path);
        fclose(file);
        return NULL;
    }
    fread(buffer, 1, length, file);
    buffer[length] = '\0';
    fclose(file);
    return buffer;
}

static u32 create_shader(const char *path, GLenum type) {
    char *source = slurp_file(path);
    u32 shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    s32 success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(success != GL_TRUE) {
        char info_log[512];
        glGetShaderInfoLog(shader, 512, NULL, info_log);
        LOG_ERROR("Failed to compile shader \"%s\". Error: %s\n", path, info_log);
        return 0;
    }
    free(source);
    return shader;
}

static b32 create_program(ShaderProgram *sp, const char *vertex_path, const char *fragment_path, void (*bind_attributes)(ShaderProgram *sp)) { // TODO: Janky implementation
    u32 vertex = create_shader(vertex_path, GL_VERTEX_SHADER);
    u32 fragment = create_shader(fragment_path, GL_FRAGMENT_SHADER);
    u32 program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    bind_attributes(sp);
    glLinkProgram(program);
    s32 success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(success != GL_TRUE) {
        char info_log[512];
        glGetProgramInfoLog(program, 512, NULL, info_log);
        LOG_ERROR("Failed to link program with shaders \"%s\" and \"%s\". Error: %s\n", vertex_path, fragment_path, info_log);
        return 0;
    }
    sp->vertex = vertex;
    sp->fragment = fragment;
    sp->program = program;
    return 1;
}

ShaderProgram create_shader_program(
    const char *vertex_path, const char *fragment_path,
    void (*bind_attributes)(ShaderProgram *sp),
    void (*get_all_uniform_locations)(ShaderProgram *sp)) {
    ShaderProgram sp = {0};
    if(create_program(&sp, vertex_path, fragment_path, bind_attributes)) {
        get_all_uniform_locations(&sp);
    } else {
        LOG_ERROR("Failed to create shader program with shaders \"%s\" and \"%s\".\n", vertex_path, fragment_path);
    }
    return sp;
}

void shader_program_start(ShaderProgram *sp) {
    glUseProgram(sp->program);
}

void shader_program_stop(void) {
    glUseProgram(0);   
}

void shader_program_cleanup(ShaderProgram *sp) {
    shader_program_stop();
    glDetachShader(sp->program, sp->vertex);
    glDetachShader(sp->program, sp->fragment);
    glDeleteShader(sp->vertex);
    glDeleteShader(sp->fragment);
    glDeleteProgram(sp->program);
}

void bind_attribute(ShaderProgram *sp, u32 attribute, const char *name) {
    glBindAttribLocation(sp->program, attribute, name);
}

void set_uniform_float(ShaderProgram *sp, const char *name, f32 v) { // TODO: Cache uniform locations for speed
    glUniform1f(glGetUniformLocation(sp->program, name), v);
}

void set_uniform_v3(ShaderProgram *sp, const char *name, vec3 v) {
    glUniform3fv(glGetUniformLocation(sp->program, name), 1, v);
}

void set_uniform_m4(ShaderProgram *sp, const char *name, mat4 m) {
    glUniformMatrix4fv(glGetUniformLocation(sp->program, name), 1, GL_FALSE, m[0]);
}
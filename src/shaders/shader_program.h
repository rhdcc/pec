#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include "external/linmath.h"
#include "utils/defines.h"

typedef struct {
    void *bind_attributes;
    u32 program, vertex, fragment;
} ShaderProgram;

ShaderProgram create_shader_program(
    const char *vertex_path, const char *fragment_path,
    void (*bind_attributes)(ShaderProgram *sp),
    void (*get_all_uniform_locations)(ShaderProgram *sp));
void shader_program_start(ShaderProgram *sp);
void shader_program_stop(void);
void shader_program_cleanup(ShaderProgram *sp);
void bind_attribute(ShaderProgram *sp, u32 attribute, const char *name);

void set_uniform_float(ShaderProgram *sp, const char *name, f32 v);
void set_uniform_v3(ShaderProgram *sp, const char *name, vec3 v);
void set_uniform_m4(ShaderProgram *sp, const char *name, mat4x4 m);

#endif // SHADER_PROGRAM_H
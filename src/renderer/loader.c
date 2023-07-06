#include "utils/log.h"
#include <stdlib.h>
#include <glad/glad.h>

#include "renderer/loader.h"

static void add_vertex_object(Loader *loader, u32 vertex_object, u32 vertex_type) {
    if(loader->vos_capacity == 0) {
        loader->vos_capacity = INITIAL_VOS_CAPACITY;
        loader->vos = malloc(loader->vos_capacity * sizeof(loader->vos[0]));
        if(!loader->vos) {
            LOG_ERROR("Failed to allocate vertex object array.\n");
            return;
        }
    } else {
        if(loader->vos_capacity < loader->vos_count + 1) {
            loader->vos_capacity = loader->vos_capacity * 2;
            loader->vos = realloc(loader->vos, loader->vos_capacity * sizeof(loader->vos[0]));
            if(!loader->vos) {
                LOG_ERROR("Failed to grow vertex object array.\n");
                return;
            }
        }
    }
    InternalVertexObject ivo = { .id = vertex_object, .type = vertex_type };
    loader->vos[loader->vos_count++] = ivo;
}

static void bind_indices_buffer(Loader *loader, u32 *indices, size_t index_len) {
    u32 ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_len * sizeof(indices[0]), indices, GL_STATIC_DRAW);
    add_vertex_object(loader, ebo, VERTEX_BUFFER);
}

static void store_in_attrib_list(Loader *loader, u32 attrib_location, u32 coordinate_num, f32 *arr, size_t arr_len) {
    u32 vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, arr_len * sizeof(arr[0]), arr, GL_STATIC_DRAW);
    glVertexAttribPointer(attrib_location, coordinate_num, GL_FLOAT, GL_FALSE, coordinate_num * sizeof(f32), (void *)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    add_vertex_object(loader, vbo, VERTEX_BUFFER);
}

RawModel load_to_vao(Loader *loader,
    u32 *indices, size_t index_len,
    f32 *vertices, size_t vertex_len) {
    RawModel m;
    glGenVertexArrays(1, &m.vao);
    glBindVertexArray(m.vao);
    bind_indices_buffer(loader, indices, index_len);
    store_in_attrib_list(loader, 0, 3, vertices, vertex_len);
    glBindVertexArray(0);
    add_vertex_object(loader, m.vao, VERTEX_ARRAY);
    m.vertex_count = (u32) index_len;
    return m;
}

void loader_cleanup(Loader *loader) {
    if(loader->vos) {
        for(size_t i = 0; i < loader->vos_count; ++i) {
            InternalVertexObject ivo = loader->vos[i];
            if(ivo.type == VERTEX_ARRAY) {
                glDeleteVertexArrays(1, &ivo.id);
            } else if(ivo.type == VERTEX_BUFFER) {
                glDeleteBuffers(1, &ivo.id);
            }
        }
        free(loader->vos);
        loader->vos = NULL;
    }
    loader->vos_capacity = 0;
    loader->vos_count = 0;
}
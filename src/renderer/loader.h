#ifndef LOADER_H
#define LOADER_H

#include <stddef.h>
#include "utils/defines.h"
#include "renderer/models.h"

#define INITIAL_VOS_CAPACITY 8
#define INITIAL_TEXTURES_CAPACITY 8

enum {
    VERTEX_ARRAY = 0,
    VERTEX_BUFFER
};

typedef struct {
    u32 type;
    u32 id;
} InternalVertexObject;

typedef struct { // TODO: Split into two different arrays to save memory
    InternalVertexObject *vos;
    size_t vos_count;
    size_t vos_capacity;
} Loader;

RawModel load_to_vao(Loader *loader,
                     u32 *indices, size_t index_len,
                     f32 *vertices, size_t vertex_len);
u32 load_texture(Loader *loader, const char *path);
void loader_cleanup(Loader *loader);

#endif // LOADER_H
#ifndef DISPLAY_H
#define DISPLAY_H

#include "utils/defines.h"

#include <GLFW/glfw3.h>

typedef struct {
    u32 width;
    u32 height;
    GLFWwindow *window;
} Display;

void display_create(s32 width, s32 height);
b32 display_should_close(void);
void display_update(void);
void display_close(void);

#endif // DISPLAY_H

#include <stdlib.h>
#include "utils/log.h"

#include <glad/glad.h>
#include "renderer/display.h"

static Display display;

static void display_framebuffer_size_cb(GLFWwindow *window, s32 width, s32 height) {
    glViewport(0, 0, width, height);
}

void display_create(s32 width, s32 height) {
    display.width = width;
    display.height = height;
    if(!glfwInit()) {
        const char *desc;
        s32 err_code = glfwGetError(&desc);
        LOG_FATAL("Failed to initialize GLFW. Code: %d, Error: %s\n", err_code, desc);
        exit(1);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow *window = glfwCreateWindow(width, height, "Hello Window", NULL, NULL);
    display.window = window;
    if(!window) {
        const char *desc;
        s32 err_code = glfwGetError(&desc);
        LOG_FATAL("Failed to create GLFW window. Code: %d, Error: %s\n", err_code, desc);
        glfwTerminate();
        exit(1);
    }
    glfwMakeContextCurrent(window);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        LOG_FATAL("Failed to initialize GLAD.\n");
        glfwTerminate();
        exit(1);
    }
    glfwSetFramebufferSizeCallback(window, display_framebuffer_size_cb);
    glViewport(0, 0, width, height);
}

b32 display_should_close(void) {
    return glfwWindowShouldClose(display.window);
}

void display_update(void) {
    glfwSwapBuffers(display.window);
    glfwPollEvents();    
}

void display_close(void) {
    glfwTerminate();
}
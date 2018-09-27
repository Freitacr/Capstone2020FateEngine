#include "GL/glew.h"
#include "GLFW/glfw3.h"
#ifndef ENGINE_RENDERING_GLFW_UTILS
#define ENGINE_RENDERING_GLFW_UTILS


int createWindowUsingParam(GLFWwindow ** windowOut, short glfwContextVersionMinor, int windowWidth, int windowHeight, const char * windowTitle);
bool windowShouldClose(GLFWwindow * window);
bool isKeyPressed(GLFWwindow * window, int keycode);

#endif
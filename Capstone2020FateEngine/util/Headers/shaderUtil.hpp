#include "GL/glew.h"

#ifndef ENGINE_RENDERING_SHADER_UTIL
#define ENGINE_RENDERING_SHADER_UTIL

GLuint createProgram(const char * vertexShaderPath, const char * fragmentShaderPath);
GLuint addProgram(const char * identifier, GLuint & program);
GLuint getProgram(const char * identifier);
GLuint removeProgram(const char * identifier);

#endif
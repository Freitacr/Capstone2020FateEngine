#include "GL/glew.h"
#ifndef ENGINE_IMAGE_LOADING_UTILITIES
#define ENGINE_IMAGE_LOADING_UTILITIES

void loadImage(const char * filename, const char * textureIdentifier);
GLuint getImage(const char * textureIdentifier);

#endif
#include "GL/glew.h"
#ifndef ENGINE_IMAGE_LOADING_UTILITIES
#define ENGINE_IMAGE_LOADING_UTILITIES

void loadImage(const char * filename, const char * textureIdentifier);
unsigned char * loadImageData(const char * filename, int *width, int * height, int * channels);
GLuint getImage(const char * textureIdentifier);

unsigned char * spliceImagesHorizontal(unsigned char * a, unsigned char * b, int & height, int & channels, int & widthA, int & widthB, int * heightOut, int * widthOut, int * channelsOut);
unsigned char * spliceImagesVertical(unsigned char * a, unsigned char * b, int & heightA, int & heightB, int & width, int & channels, int * heightOut, int * widthOut, int * channelsOut);

#endif
#include <vector>
#include "GL/glew.h"

#ifndef ENGINE_BASE_RENDER_CLASS
#define ENGINE_BASE_RENDER_CLASS

class RenderingObject {

private:
	std::vector<GLuint> renderingData;
	std::vector<GLuint> textureSlots;
	const std::string programIdentifier;
	float & x, &y, &z;
	const GLfloat *position, *normal, *uv;
	const GLfloat * model;
	void setupRenderingData(const GLfloat * position, size_t & positionSize, const GLfloat * normal, size_t & normalSize, const GLfloat * uv, size_t & uvSize);
	void setupVertexArray();
	void setupBuffer(const GLfloat * data, size_t size);
	void setupTextures(std::vector<const char *> & textureFilePaths, std::vector<const char *> & identifiers);

public:
	RenderingObject(float x, float y, float z, const GLfloat * position, size_t & positionSize, const GLfloat * normal, size_t & normalSize, const GLfloat * uv, size_t & uvSize, std::vector<const char *> & textureID, std::vector<const char *> & texIdentifier, const std::string & programIdentifier);
	void render();
	const std::string * getProgramIdentifier();
};

#endif
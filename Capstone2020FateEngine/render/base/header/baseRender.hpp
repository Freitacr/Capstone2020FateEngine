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
	const GLfloat * model;
	void setupRenderingData(const GLfloat * position, size_t & positionSize, const GLfloat * normal, size_t & normalSize, const GLfloat * uv, size_t & uvSize, const GLuint * elements, size_t & eleSize);
	void setupVertexArray();
	void setupBuffer(const GLfloat * data, size_t size);
	void setupTextures(std::vector<const char *> & textureFilePaths, std::vector<const char *> & identifiers);
	void copy(const RenderingObject & other);
	void setupElements(const GLuint * data, size_t size);


public:
	RenderingObject(float x, float y, float z, const GLfloat * position, size_t & positionSize, const GLfloat * normal, size_t & normalSize, const GLfloat * uv, size_t & uvSize, const GLuint * elements, size_t & eleSize, std::vector<const char *> & textureID, std::vector<const char *> & texIdentifier, const std::string & programIdentifier);
	RenderingObject(const RenderingObject & other);
	RenderingObject(float x, float y, float z, const char * id);
	RenderingObject operator=(const RenderingObject & other);
	void render();
	const std::string * getProgramIdentifier();
	void reassignReferences(float x, float y, float z);
	void setTextures(std::vector<const char *> & textureFilenames, std::vector<const char *> & textureIdentifiers);
};

#endif
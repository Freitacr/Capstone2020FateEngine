#include "../../base/header/baseRender.hpp"
#include "../header/quad.hpp"
#include "GL/glew.h"
#include <vector>

void Quad::setupRenderingData() {
	static const GLfloat vertexBuff[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f
	};

	static const GLfloat uvBuff[] = {
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
	};

	static const GLfloat normBuff[] = {
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f
	};

	static const GLuint elementBuff[] = {
		0,1,2,
		2,3,0
	};

	size_t vSize = sizeof(vertexBuff), uvSize = sizeof(uvBuff), nSize = sizeof(normBuff), eSize = sizeof(elementBuff);

	std::vector<const char *> filenames, identifiers;
	const std::string progId("NULL");
	rData = RenderingObject(0.0f, 0.0f, 0.0f, vertexBuff, vSize, normBuff, nSize, uvBuff, uvSize, elementBuff, eSize, filenames, identifiers, progId);
}

Quad::Quad() : rData(x, y, z, ""){
	setupRenderingData();
}

Quad::Quad(float globalX, float globalY, float globalZ, std::vector<const char *> & textureFileNames, std::vector<const char *> & textureIdentifiers) : rData(x, y, z, "") {
	setupRenderingData();
	x = globalX;
	y = globalY;
	z = globalZ;
	rData.setTextures(textureFileNames, textureIdentifiers);
}

void Quad::render() {
	rData.render();
}

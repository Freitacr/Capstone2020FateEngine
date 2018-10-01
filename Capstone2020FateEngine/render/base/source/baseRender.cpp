#include <vector>
#include "GL/glew.h"
#include "../header/baseRender.hpp"
#include "../../../util/Headers/imageUtil.hpp"

void RenderingObject::render() {
	//Assume program has already been set
	glBindVertexArray(renderingData[0]);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, renderingData[1]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, renderingData[2]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, renderingData[3]);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	
	if (textureSlots.size()) {
		for (size_t i = 0; i < textureSlots.size(); i++) {
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, textureSlots[i]);
		}
	}
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawArrays(GL_TRIANGLES, 3, 3);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	//if (textureSlots.size()) {
	//	for (size_t i = 0; i < textureSlots.size(); i++) {
	//		glActiveTexture(GL_TEXTURE0 + i);
	//		glBindTexture(GL_TEXTURE_2D, 0);
	//	}
	//}
}

void RenderingObject::setupVertexArray() {
	GLuint vArray;
	glGenVertexArrays(1, &vArray);
	glBindVertexArray(vArray);
	renderingData.push_back(vArray);
}

void RenderingObject::setupBuffer(const GLfloat * data, size_t size) {
	GLuint vBuffer;
	glGenBuffers(1, &vBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vBuffer);
	glBufferData(GL_ARRAY_BUFFER, size, (void*)data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, NULL);
	renderingData.push_back(vBuffer);
}

void RenderingObject::setupRenderingData(const GLfloat * position, size_t & positionSize, const GLfloat * normal, size_t & normalSize, const GLfloat * uv, size_t & uvSize) {
	setupVertexArray();
	setupBuffer(position, positionSize);
	setupBuffer(normal, normalSize);
	setupBuffer(uv, uvSize);
	glBindVertexArray(renderingData[0]);
}

void RenderingObject::setupTextures(std::vector<const char *> & textureFilePaths, std::vector<const char *> & identifiers) {
	for (size_t i = 0; i < textureFilePaths.size(); i++) {
		const char * identifier = identifiers[i];
		const char * textureFilePath = textureFilePaths[i];
		GLuint texID;

		if ((texID = getImage(identifier))) {
			//Assume that this is an intended thing, and just use it
		}
		else {
			loadImage(textureFilePath, identifier);
			texID = getImage(identifier);
		}
		textureSlots.push_back(texID);
	}
}


RenderingObject::RenderingObject(float globX, float globY, float globZ, const GLfloat * position, size_t & positionSize, const GLfloat * normal, size_t & normalSize, const GLfloat * uv, size_t & uvSize, std::vector<const char *> & textureID, std::vector<const char *> & texIdentifier, const std::string & programIdentifier) : x(x), y(y), z(z), programIdentifier(programIdentifier) {
	setupRenderingData(position, positionSize, normal, normalSize, uv, uvSize);
	setupTextures(textureID, texIdentifier);
}

const std::string * RenderingObject::getProgramIdentifier() {
	return &programIdentifier;
}


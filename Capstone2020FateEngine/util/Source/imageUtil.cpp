#include <iostream>
#include <map>
#include "GL/glew.h"
#include "soil.h"

class ImageCloset {

private:
	std::map<std::string, GLuint> data;
public:
	ImageCloset() {

	}

	GLuint addTexture(std::string identifier, GLuint texID) {
		GLuint prev = data[identifier];
		data[identifier] = texID;
		return prev;
	}

	GLuint getTexture(std::string identifier) {
		return data[identifier];
	}

};

ImageCloset imgStorage{};

GLuint getImage(const char * textureIdentifier) {
	return imgStorage.getTexture(std::string(textureIdentifier));
}

void loadImage(const char * filename, const char * textureIdentifier) {
	if (getImage((textureIdentifier))) {
		return;
	}
	
	int width, height, channels;
	unsigned char * data = SOIL_load_image(filename, &width, &height, &channels, SOIL_LOAD_AUTO);

	GLuint textureID;
	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)data);
	
	//These work on the GL_TEXTURE_2D "hook", basically think of it as backlogging steps to do (if the hook is empty)
	//or doing the steps to whatever is hooked on the "hook"

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	//Clear the hook (yes the images are saved even when you do this. Weird, but true)
	glBindTexture(GL_TEXTURE_2D, NULL);

	//Free image data from memory, so it only exists within the openGL memory
	SOIL_free_image_data(data);
	imgStorage.addTexture(std::string(textureIdentifier), textureID);
}



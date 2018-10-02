#include <iostream>
#include <map>
#include "GL/glew.h"
#include "soil.h"

unsigned char * loadImageData(const char * filename, int *width, int * height, int * channels) {
	return SOIL_load_image(filename, width, height, channels, SOIL_LOAD_AUTO);
}

GLuint giveTextureToGL(unsigned char * data, int &width, int &height, int &channels) {

	GLuint textureID;
	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)data);

	//These work on the GL_TEXTURE_2D "hook", basically think of it as backlogging steps to do (if the hook is empty)
	//or doing the steps to whatever is hooked on the "hook"

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	//Clear the hook (yes the images are saved even when you do this. Weird, but true)
	glBindTexture(GL_TEXTURE_2D, NULL);
	return textureID;
}

unsigned char * spliceImagesHorizontal(unsigned char * a, unsigned char * b, int & height, int & channels, int & widthA, int & widthB, int * heightOut, int * widthOut, int * channelsOut) {
	//This method assumes that the heights and channels of the two images are identical
	size_t size = height * (widthA + widthB) * channels;
	unsigned char * ret = (unsigned char *)malloc(size * sizeof(unsigned char));
	if (ret) {
		(*widthOut) = widthA + widthB;
		(*heightOut) = height;
		(*channelsOut) = channels;

		for (int i = 0; i < height; i++) {
			int row_pos = 0;
			for (int j = 0; j < widthA * channels; j++) {
				ret[(i * (*widthOut) * channels) + row_pos] = a[(i * widthA * channels) + j];
				row_pos++;
			}

			for (int j = 0; j < widthB * channels; j++) {
				ret[(i * (*widthOut) * channels) + row_pos] = b[(i * widthB * channels) + j];
				row_pos++;
			}
		}
	}

	return ret;
}

unsigned char * spliceImagesVertical(unsigned char * a, unsigned char * b, int & heightA, int & heightB, int & width, int & channels, int * heightOut, int * widthOut, int * channelsOut) {
	size_t size = width * (heightA + heightB) * channels;
	unsigned char * ret = (unsigned char *)malloc(size * sizeof(unsigned char));

	if (ret) {
		(*widthOut) = width;
		(*heightOut) = heightA + heightB;
		(*channelsOut) = channels;

		int heightPos = 0;
		for (int i = 0; i < heightA; i++) {
			for (int j = 0; j < width * channels; j++) {
				ret[(heightPos * (*widthOut) * (*channelsOut)) + j] = a[(i * width * channels) + j];
			}
			heightPos++;
		}
		for (int i = 0; i < heightB; i++) {
			for (int j = 0; j < width * channels; j++) {
				ret[(heightPos * (*widthOut) * (*channelsOut)) + j] = a[(i * width * channels) + j];
			}
			heightPos++;
		}

	}

	return ret;
}

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
	unsigned char * data = loadImageData(filename, &width, &height, &channels);

	GLuint textureID = giveTextureToGL(data, width, height, channels);

	//Free image data from memory, so it only exists within the openGL memory
	SOIL_free_image_data(data);
	imgStorage.addTexture(std::string(textureIdentifier), textureID);
}




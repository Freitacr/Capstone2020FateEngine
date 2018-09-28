#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include "GL/glew.h"



std::map<std::string, GLuint> programMap;

GLuint compileShader(std::ifstream & shaderStream, GLenum shaderType) {
	GLuint shaderID = glCreateShader(shaderType);
	
	GLint compilationRes;
	int infoLogLen;
	
	std::stringstream buffer;
	std::string storageStep;

	buffer << shaderStream.rdbuf();
	storageStep = buffer.str();
	const char * baseLevelPointer = storageStep.c_str();

	glShaderSource(shaderID, 1, &baseLevelPointer, NULL);
	glCompileShader(shaderID);

	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compilationRes);
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLen);
	if (infoLogLen > 0) {
		std::vector<char> errorMessage(infoLogLen + 1);
		glGetShaderInfoLog(shaderID, infoLogLen, NULL, &errorMessage[0]);
		std::cout << &errorMessage[0] << std::endl;
	}
	return shaderID;
}

void linkShaders(GLuint & programID, GLuint & vertexShader, GLuint & fragmentShader) {
	GLint linkResult;
	int infoLogLength;
	
	programID = glCreateProgram();
	glAttachShader(programID, vertexShader);
	glAttachShader(programID, fragmentShader);
	glLinkProgram(programID);

	glGetProgramiv(programID, GL_LINK_STATUS, &linkResult);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0) {
		std::vector<char> errorMessage(infoLogLength + 1);
		glGetShaderInfoLog(programID, infoLogLength, NULL, &errorMessage[0]);
		std::cout << &errorMessage[0] << std::endl;
	}

	glDetachShader(programID, vertexShader);
	glDetachShader(programID, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

GLuint createProgram(const char * vertexShaderPath, const char * fragmentShaderPath) {
	/* Ignore this unless it doesn't work. This is back end shader code stuff
	As of right now it stands untested, but there are very few reasons why it shouldn't work...
	*/

	GLuint programID;
	std::stringstream buffer{};
	std::string buf;
	
	std::ifstream vertexInStream(vertexShaderPath);
	std::ifstream fragmentInStream(fragmentShaderPath);
	if (vertexInStream.is_open() && fragmentInStream.is_open()) {
		GLuint vertexShader, fragmentShader;
		
		vertexShader = compileShader(vertexInStream, GL_VERTEX_SHADER);
		fragmentShader = compileShader(fragmentInStream, GL_FRAGMENT_SHADER);
		
		linkShaders(programID, vertexShader, fragmentShader);
	}
	else {
		if (!fragmentInStream.is_open()) {
			std::cerr << "Fragment Shader at " << fragmentShaderPath << " does not exist..." << std::endl;
		}
		if (!vertexInStream.is_open()) {
			std::cerr << "Vertex Shader at " << vertexShaderPath << " does not exist..." << std::endl;
		}
		return 0;
	}

	return programID;

}

GLuint addProgram(const char * identifier, GLuint & program) {
	std::string key(identifier);
	GLuint prev = programMap[key];
	programMap[key] = program;
	return prev;
}

GLuint getProgram(const char * identifier) {
	return programMap[std::string(identifier)];
}

GLuint removeProgram(const char * identifier) {
	std::string key(identifier);
	GLuint prev = programMap[key];
	programMap.erase(key);
	return prev;
}


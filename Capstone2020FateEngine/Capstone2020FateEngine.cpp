// Capstone2020FateEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "util/Headers/glfwUtil.hpp"
#include "util/Headers/shaderUtil.hpp"
#include "util/Headers/imageUtil.hpp"
#include "render/base/header/baseRender.hpp"
#include "render/shapes/header/quad.hpp"

GLFWwindow * mainWindow;

int main()
{
	//Create window
	int res = createWindowUsingParam(&mainWindow, 4, 1024, 800, "TestWindow");
	
	/*
	Backend testing stuff... Ignore this...
	*/
	static const GLfloat vertexBuff[] = { 
		-1.0f, -1.0f, 0.0f, 
		1.0f, -1.0f, 0.0f, 
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f
		};

	static const GLfloat uvBuff[] = { 
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f
		};

	static const GLfloat normBuff[] = {
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 
		0.0f, 0.0f, 1.0f, 
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 
		0.0f, 0.0f, 1.0f 
		};

	GLuint program = createProgram("textureVertexShader.vs", "textureFragmentShader.fs");
	
	std::vector<const char *> textureFilenames, identifiers;
	textureFilenames.push_back("TileUVExport.png");
	identifiers.push_back("mainTex");

	Quad x(0, 0, 0, textureFilenames, identifiers);

	if (res != 0) {
		std::cerr << "Error occurred while creating window. This is bad.\n";
		exit(res);
	}

	//Capture Key Presses
	glfwSetInputMode(mainWindow, GLFW_STICKY_KEYS, GL_TRUE);

	//These two would exist within the render() function of a class that does transparency. So TransparentQuad, etc.
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);


	do {
		//Clear the back buffer (this will also include a depth buffer bit later)
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Do rendering work here

		
		
		glUseProgram(program);
		
		x.render();

		//Swap buffers, showing the work that you just did
		glfwSwapBuffers(mainWindow);
		//Poll events so we know whether we should close or not.
		glfwPollEvents();
	} while (!(isKeyPressed(mainWindow, GLFW_KEY_ESCAPE) || windowShouldClose(mainWindow)));

}

// Capstone2020FateEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "util/Headers/glfwUtil.hpp"
#include "util/Headers/shaderUtil.hpp"
#include "util/Headers/imageUtil.hpp"
#include "soil.h"

GLFWwindow * mainWindow;

int main()
{
	//Create window
	int res = createWindowUsingParam(&mainWindow, 4, 1024, 800, "TestWindow");
	
	/*
	Backend testing stuff... Ignore this...
	*/
	static const GLfloat vertexBuff[] = { -1.0f, -1.0f, 0.0f, 
		1.0f, -1.0f, 0.0f, 
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f};

	static const GLfloat uvBuff[] = { 0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f };

	GLuint vertArray;
	glGenVertexArrays(1, &vertArray);
	glBindVertexArray(vertArray);


	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBuff), vertexBuff, GL_STATIC_DRAW);

	GLuint uvBuffer;
	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvBuff), uvBuff, GL_STATIC_DRAW);

	loadImage("Village of the Talon Battle Map.png", "mainTex");
	GLuint tex = getImage("mainTex");

	


	GLuint program = createProgram("textureVertexShader.vs", "textureFragmentShader.fs");


	if (res != 0) {
		std::cerr << "Error occurred while creating window. This is bad.\n";
		exit(res);
	}

	//Capture Key Presses
	glfwSetInputMode(mainWindow, GLFW_STICKY_KEYS, GL_TRUE);

	do {
		//Clear the back buffer (this will also include a depth buffer bit later)
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(program);

		//Do rendering work here
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex);

		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawArrays(GL_TRIANGLES, 3, 3);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glActiveTexture(NULL);



		//Swap buffers, showing the work that you just did
		glfwSwapBuffers(mainWindow);
		//Poll events so we know whether we should close or not.
		glfwPollEvents();
	} while (!(isKeyPressed(mainWindow, GLFW_KEY_ESCAPE) || windowShouldClose(mainWindow)));

}

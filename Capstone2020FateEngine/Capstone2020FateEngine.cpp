// Capstone2020FateEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "util/Headers/glfwUtil.hpp"
#include "util/Headers/shaderUtil.hpp"


GLFWwindow * mainWindow;

int main()
{
	//Create window
	int res = createWindowUsingParam(&mainWindow, 4, 1024, 800, "TestWindow");
	
	static const GLfloat vertexBuff[] = { -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f };

	GLuint vertArray;
	glGenVertexArrays(1, &vertArray);
	glBindVertexArray(vertArray);



	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBuff), vertexBuff, GL_STATIC_DRAW);

	GLuint program = createProgram("simpleVertShader.vertexShader", "simpleFragmentShader.fragmentShader");


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
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);



		//Swap buffers, showing the work that you just did
		glfwSwapBuffers(mainWindow);
		//Poll events so we know whether we should close or not.
		glfwPollEvents();
	} while (!(isKeyPressed(mainWindow, GLFW_KEY_ESCAPE) || windowShouldClose(mainWindow)));

}

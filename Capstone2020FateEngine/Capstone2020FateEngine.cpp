// Capstone2020FateEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "util/Headers/glfwUtil.hpp"
#include <iostream>


GLFWwindow * mainWindow;

int main()
{
	//Create window
	//Parameters after the pointer to mainWindow:
		/*
			Antialiasing Samples,

		*/
	int res = createWindowUsingParam(&mainWindow, 4, 1024, 800, "TestWindow");

	if (res != 0) {
		std::cerr << "Error occurred while creating window. This is bad.\n";
		exit(res);
	}

	//Capture Key Presses
	glfwSetInputMode(mainWindow, GLFW_STICKY_KEYS, GL_TRUE);

	do {
		//Clear the back buffer (this will also include a depth buffer bit later)
		glClear(GL_COLOR_BUFFER_BIT);

		//Do rendering work here


		//Swap buffers, showing the work that you just did
		glfwSwapBuffers(mainWindow);
		//Poll events so we know whether we should close or not.
		glfwPollEvents();
	} while (!(isKeyPressed(mainWindow, GLFW_KEY_ESCAPE) || windowShouldClose(mainWindow)));

}

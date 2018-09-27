#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "GL/freeglut.h"
#include "../Headers/glfwUtil.hpp"


int createWindowUsingParam(GLFWwindow ** windowOut, short antiAliasingSamples, int windowWidth, int windowHeight, const char * windowTitle) {
	//This is needed to use the core profile, which is the most up to date.
	glewExperimental = true;

	//This has to be done before any windows can be created successfully. Key word successfully. There is no error for attempting it...
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW\n";
		return -1;
	}

	//Give the window some ideas about what it should be.
	glfwWindowHint(GLFW_SAMPLES, antiAliasingSamples);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Yes, dereferencing to a pointer, this needs to happen to actually assign the value to the pointer.
	(*windowOut) = glfwCreateWindow(windowWidth, windowHeight, windowTitle, NULL, NULL);
	
	//Error Catching.
	if ((*windowOut) == NULL) {
		std::cerr << "Failed to open GLFW window.\n";
		glfwTerminate();
		return -1;
	}

	//This initializes GLEW
	glfwMakeContextCurrent(*windowOut);


	//Finish GLEW initialization.
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW\n";
		return -1;
	}


	return 0;
}

bool windowShouldClose(GLFWwindow * window) {
	return glfwWindowShouldClose(window) >= 1;
}

bool isKeyPressed(GLFWwindow * window, int keycode) {
	return glfwGetKey(window, keycode) == GLFW_PRESS;
}
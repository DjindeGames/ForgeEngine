#pragma once

#include <string>

struct GLFWwindow;

namespace ForgeEngine
{
	typedef unsigned int GL_ID;
	typedef int GL_RESULT;

	#define TOGGLE_WIREFRAME GLFW_KEY_Q
	#define GL_NULL_ID 0

	//Inits and return a GLFWWindow
	GLFWwindow* InitWindow(std::string name, unsigned int width, unsigned int height);
}
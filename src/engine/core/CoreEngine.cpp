#include "CoreEngine.h"

#include "engine/core/GameHandler.h"
#include "engine/core/OpenGL.h"

#include <iostream>

namespace ForgeEngine
{
	//glfw: whenever the window size changed (by OS or user resize) this callback function executes
	void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		//make sure the viewport matches the new window dimensions; note that width and 
		//height will be significantly larger than specified on retina displays.
		glViewport(0, 0, width, height);
		GameHandler::m_WindowWidth = width;
		GameHandler::m_WindowHeight = height;
	}

	GLFWwindow* InitWindow(std::string name, unsigned int width, unsigned int height)
	{
		//glfw: initialize and configure
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		//glfw window creation
		GLFWwindow* window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
		if (window == nullptr)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return nullptr;
		}
		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

		//glad: load all OpenGL function pointers
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return nullptr;
		}

		return window;
	}
}
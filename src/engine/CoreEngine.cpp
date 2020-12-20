#include "CoreEngine.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void CreateWindowAndStartLoop(std::string name, unsigned int width, unsigned int height)
{
	if (GLFWwindow * window = InitWindow("Forge Engine", width, height))
	{
		// render loop
		// -----------
		while (!glfwWindowShouldClose(window))
		{
			// input
			// -----
			ProcessInput(window);

			// render
			// set state color
			glClearColor(1.f, 1.f, 1.f, 1.f);
			// applies state
			glClear(GL_COLOR_BUFFER_BIT);

			// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
			// -------------------------------------------------------------------------------
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
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
	if (window == NULL)
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

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	//make sure the viewport matches the new window dimensions; note that width and 
	//height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow* window)
{
	if (WantsToTerminate(window))
	{
		glfwSetWindowShouldClose(window, true);
	}
}

bool WantsToTerminate(GLFWwindow* window)
{
	int key = glfwGetKey(window, GLFW_KEY_ESCAPE) || glfwGetKey(window, GLFW_KEY_ENTER);
	return (key == GLFW_PRESS);
}
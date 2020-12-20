#pragma once

#include <string>

class GLFWwindow;

//Creates a window and handles the main loop
void CreateWindowAndStartLoop(std::string name, unsigned int width, unsigned int height);
//Inits and return a GLFWWindow
GLFWwindow* InitWindow(std::string name, unsigned int width, unsigned int height);
//glfw: whenever the window size changed (by OS or user resize) this callback function executes
void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
//Process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void ProcessInput(GLFWwindow* window);
//Returns true if the user wants to terminate
bool WantsToTerminate(GLFWwindow* window);
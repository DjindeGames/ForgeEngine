#include "PapierKraft.h"

#include "../engine/Game.h"
#include "../engine/ShaderUtils.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace ForgeEngine;

int main()
{
	return PapierKraft::CoreLoop();
}

namespace PapierKraft
{
	/****************************************/
	/************* GLOBAL DATA **************/
	/****************************************/

	//Basic vertex shader code (written in GLSL)
	const char* vertexShaderSource =
		"#version 330 core\n"
		//This location = 0 is still a bit mysterious...
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	//Basic fragment shader code (written in GLSL)
	const char* fragmentShaderSource =
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()"
		"{\n"
		"	FragColor = vec4(1.f, 0.f, 0.f, 1.f);\n"
		"}\n";

	//First triangle
	const float triangleVertices[] = {
		//    x      y     z
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
	};

	GL_ID vertexShader{}, fragmentShader{}, shaderProgram{}, vertexBufferObject{}, vertexArrayObject{};

	/****************************************/
	/************** FUCNTIONS ***************/
	/****************************************/

	int CoreLoop()
	{
		Game game{};
		game.Init("PapierKraft", 800, 600);
		game.SetUpdateCallback(Update);
		game.SetTerminationConditionCallback(ShouldTerminate);

		if (!CompileShaders())
		{
			return -1;
		}
		BuildTriangle();

		game.StartLoop();
		
		ClearResources();

		return 0;
	}

	void Update(float dT)
	{
		// set state color
		glClearColor(1.f, 1.f, 1.f, 1.f);
		// applies state
		glClear(GL_COLOR_BUFFER_BIT);
		//Draw triangle
		glUseProgram(shaderProgram);
		glBindVertexArray(vertexArrayObject);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	bool ShouldTerminate(GLFWwindow* window)
	{
		return (
			glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS ||
			glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS
			);
	}

	bool CompileShaders()
	{
		//Create and compile both vertex shader (geometry) and fragment shader (color) and links them into one shader program
		if (
			!TryCompileShader(vertexShader, vertexShaderSource, GL_VERTEX_SHADER) || 
			!TryCompileShader(fragmentShader, fragmentShaderSource, GL_FRAGMENT_SHADER) ||
			!TryLinkShaderProgram(shaderProgram, true, &vertexShader, &vertexShaderSource)
		)
		{
			return false;
		}
		return true;
	}

	void BuildTriangle()
	{
		//Generates buffer to store vertices
		glGenBuffers(1, &vertexBufferObject);
		glGenVertexArrays(1, &vertexArrayObject);
		
		//Bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		
		//1. Bind Vertex Array Object
		glBindVertexArray(vertexArrayObject);
		
		//2. Copy our vertices array in a buffer for OpenGL to use
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
		glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);
		
		//3. Then set our vertex attributes pointers
		//First argument corresponds to the vertex attribute location (comes from vertexShaderSource)
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		//Argument corresponds to the vertex attribute location
		glEnableVertexAttribArray(0);

		//Unbinding, this is optionnal

		//Note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		//You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
		//VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
		glBindVertexArray(0);
	}

	void ClearResources()
	{
		glDeleteVertexArrays(1, &vertexArrayObject);
		glDeleteBuffers(1, &vertexBufferObject);
		glDeleteProgram(shaderProgram);
	}
}
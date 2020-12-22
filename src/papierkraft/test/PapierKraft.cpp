#include "PapierKraft.h"

#include "engine/misc/Color.h"
#include "engine/core/Game.h"
#include "engine/math/Vector3.h"
#include "engine/3d/Mesh.h"
#include "engine/shader/ShaderUtils.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

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

	Game game{};
	std::vector<Mesh> meshes{};
	GL_ID vertexShader{}, fragmentShader{}, shaderProgram{}, vertexBufferObject{};

	/****************************************/
	/************** FUNCTIONS ***************/
	/****************************************/

	int CoreLoop()
	{
		PerformTests();

		game.Init("PapierKraft", 800, 600);
		game.SetUpdateCallback(Update);
		game.SetTerminationConditionCallback(ShouldTerminate);

		if (!CompileShaders())
		{
			return -1;
		}
		BuildMesh();

		game.StartLoop();
		
		ClearResources();

		return 0;
	}

	void Update(float dT)
	{
		ProcessInput();
		// set state color
		glClearColor(1.f, 1.f, 1.f, 1.f);
		// applies state
		glClear(GL_COLOR_BUFFER_BIT);

		for (Mesh mesh : meshes)
		{
			mesh.Render();
		}
	}

	void PerformTests()
	{
	}

	void ProcessInput()
	{
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

	void BuildMesh()
	{
		std::vector<Vector3> vertices {
			Vector3{-0.5f, -0.5f, 0.0f},
			Vector3{-0.5f,  0.5f, 0.0f},
			Vector3{ 0.5f, -0.5f, 0.0f},
		};
		
		meshes.push_back(Mesh{ vertices, shaderProgram });
	}

	void BuildMesh2()
	{
		std::vector<Vector3> vertices{
			Vector3{-0.5f, -0.5f, 0.0f},
			Vector3{-0.5f,  0.5f, 0.0f},
			Vector3{ 0.5f, -0.5f, 0.0f},
			Vector3{-0.5f,  0.5f, 0.0f}
		};

		//Coordinate indexes 
		std::vector<unsigned int> triangleIndices = {
			//First triangle
				0, 1, 2,
			//Second triangle
				1, 2, 3
		};

		meshes.push_back(Mesh{ vertices, shaderProgram, triangleIndices });
	}

	void ClearResources()
	{
		glDeleteProgram(shaderProgram);
	}
}
#include "PapierKraft.h"

#include "engine/3d/MeshFactory.h"
#include "engine/core/Game.h"
#include "engine/math/Vector3.h"
#include "engine/misc/Color.h"
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
	//Try anything here
	void PerformTests()
	{
	}

	int CoreLoop()
	{
		PerformTests();

		Game game{};
		game.Init("PapierKraft", 800, 600);
		game.SetUpdateCallback(Update);
		game.SetTerminationConditionCallback(ShouldTerminate);

		BuildMeshes();

		game.HandleProcess();
		
		return 0;
	}

	void Update(float dT)
	{
		ProcessInput();
		ShaderUtils::SetBackgroundColor(COLOR_BLACK);
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

	void BuildMeshes()
	{
		std::vector<Vector3> vertices1{
			Vector3{-0.5f, -0.5f, 0.0f},
			Vector3{ 0.f,  0.5f, 0.0f},
			Vector3{ 0.5f, -0.5f, 0.0f}
		};

		std::vector<Vector3> vertices2{
			Vector3{ 0.5f, 0.5f, 0.0f},
			Vector3{ 1.f,  1.5f, 0.0f},
			Vector3{ 1.5f, 0.5f, 0.0f}
		};

		//Coordinate indexes 
		std::vector<unsigned int> triangleIndices = {
			//First triangle
				0, 1, 2
		};

		MeshFactory::RegisterMesh(vertices1, triangleIndices, COLOR_GREEN);
		MeshFactory::RegisterMesh(vertices2, triangleIndices, COLOR_RED);
	}
}
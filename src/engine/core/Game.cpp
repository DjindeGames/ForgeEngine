#include "Game.h"

#include "common/managers/ShaderManager.h"
#include "engine/core/CoreEngine.h"
#include "engine/core/Entity.h"
#include "engine/core/ManagerContainer.h"
#include "engine/core/OpenGL.h"
#include "engine/shader/ShaderUtils.h"

#include <chrono>
#include <cmath>
#include <iostream>

namespace ForgeEngine
{
	GLFWwindow* Game::m_Window{};

	bool Game::Init(std::string name, unsigned int width, unsigned int height)
	{
		if (m_Window = InitWindow(name, width, height))
		{
			return true;
		}
		return false;
	}

	void Game::HandleProcess()
	{
		using ns = std::chrono::nanoseconds;

		std::chrono::time_point<std::chrono::high_resolution_clock> frameStart = std::chrono::high_resolution_clock::now();
		std::chrono::time_point<std::chrono::high_resolution_clock> frameEnd = std::chrono::high_resolution_clock::now();

		float dT{};
		const float nanoToSecMultiplier = std::pow(10, 9);

		if (m_Window != nullptr)
		{
			OnInit();

			ManagerContainer::Get()->PreInit();
			EntityContainer::Get()->PreInit();
			ManagerContainer::Get()->Init();
			EntityContainer::Get()->Init();
			ManagerContainer::Get()->PostInit();
			EntityContainer::Get()->PostInit();

			while (!ShouldTerminate())
			{
				//deltaTime is defined using seconds
				dT = std::chrono::duration_cast<ns>(frameEnd - frameStart).count() / nanoToSecMultiplier;
				frameStart = std::chrono::high_resolution_clock::now();

				OnUpdate(dT);

				ManagerContainer::Get()->PreUpdate(dT);
				EntityContainer::Get()->PreUpdate(dT);
				ManagerContainer::Get()->Update(dT);
				EntityContainer::Get()->Update(dT);
				ManagerContainer::Get()->PostUpdate(dT);
				EntityContainer::Get()->PostUpdate(dT);

				// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
				glfwSwapBuffers(m_Window);
				glfwPollEvents();

				frameEnd = std::chrono::high_resolution_clock::now();
			}

			OnTermination();
		}
	}

	void Game::OnInit()
	{
	}

	void Game::OnTermination()
	{
		// glfw: terminate, clearing all previously allocated GLFW resources.
		glfwTerminate();
	}

	bool Game::ShouldTerminate()
	{
		return (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS);
	}
}
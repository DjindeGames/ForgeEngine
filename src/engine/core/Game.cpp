#include "Game.h"

#include "engine/core/CoreEngine.h"
#include "engine/core/Entity.h"
#include "engine/shader/ShaderUtils.h"

#include <chrono>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace ForgeEngine
{
	Game::Game() : m_CurrentDrawMode(GL_FILL)
	{
	}

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
		float nanoToSecMultiplier = std::pow(10, 9);

		if (m_Window != nullptr)
		{
			Entity::PreInit();
			Entity::Init();
			Entity::PostInit();

			while (!glfwWindowShouldClose(m_Window))
			{
				//deltaTime is defined using seconds
				dT = std::chrono::duration_cast<ns>(frameEnd - frameStart).count() / nanoToSecMultiplier;
				frameStart = std::chrono::high_resolution_clock::now();

				if (m_UpdateCallback)
				{
					m_UpdateCallback(dT);
				}

				Entity::PreUpdate();
				Entity::Update(dT);
				Entity::PostUpdate();

				ProcessDebugInput();

				CheckTermination();

				// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
				glfwSwapBuffers(m_Window);
				glfwPollEvents();

				frameEnd = std::chrono::high_resolution_clock::now();
			}

			OnTermination();

			// glfw: terminate, clearing all previously allocated GLFW resources.
			glfwTerminate();
		}
	}

	void Game::CheckTermination()
	{
		bool shouldTerminate = false;
		if (m_TerminationConditionCallback)
		{
			shouldTerminate = m_TerminationConditionCallback(m_Window);
		}
		else
		{
			shouldTerminate = DefaultTerminationCondition();
		}
		glfwSetWindowShouldClose(m_Window, shouldTerminate);
	}

	void Game::OnTermination()
	{
		Entity::ReleaseEntities();
	}

	bool Game::DefaultTerminationCondition()
	{
		return (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS);
	}

	void Game::ProcessDebugInput()
	{
		if (glfwGetKey(m_Window, TOGGLE_WIREFRAME) == GLFW_PRESS)
		{
			ToggleWireframeMode();
		}
	}

	void Game::ToggleWireframeMode()
	{
		int newDrawMode = ((m_CurrentDrawMode == GL_LINE) ? GL_FILL : GL_LINE);
		glPolygonMode(GL_FRONT_AND_BACK, newDrawMode);
		m_CurrentDrawMode = newDrawMode;
	}
}
#include "Game.h"

#include "CoreEngine.h"
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

	void Game::StartLoop()
	{
		if (m_Window != nullptr)
		{
			while (!glfwWindowShouldClose(m_Window))
			{
				CheckTermination();

				if (m_UpdateCallback)
				{
					m_UpdateCallback(0.f);
				}

				ProcessDebugInput();

				// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
				glfwSwapBuffers(m_Window);
				glfwPollEvents();
			}
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
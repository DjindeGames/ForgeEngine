#include "GameHandler.h"

#include "common/managers/ShaderManager.h"
#include "engine/core/ForgeEngine.h"
#include "engine/shader/ShaderUtils.h"
#include "engine/ui/ImGUI.h"

#include <chrono>
#include <cmath>
#include <iostream>

namespace ForgeEngine
{
	GLFWwindow* GameHandler::m_Window{};
	unsigned int GameHandler::m_WindowWidth{};
	unsigned int GameHandler::m_WindowHeight{};

	bool GameHandler::Init(std::string name, unsigned int width, unsigned int height)
	{
		m_WindowWidth = width;
		m_WindowHeight = height;
		if (m_Window = InitWindow(name, width, height))
		{
			return true;
		}
		return false;
	}

	void GameHandler::HandleProcess()
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

				// feed inputs to dear imgui, start new frame
				#ifdef FORGE_DEBUG_MODE
					ImGui_ImplOpenGL3_NewFrame();
					ImGui_ImplGlfw_NewFrame();
					ImGui::NewFrame();

					ManagerContainer::Get()->DrawDebug(dT);
					EntityContainer::Get()->DrawDebug(dT);

					// Render dear imgui into screen
					ImGui::Render();
					ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
				#endif // FORGE_DEBUG_MODE

				// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
				glfwSwapBuffers(m_Window);
				glfwPollEvents();

				frameEnd = std::chrono::high_resolution_clock::now();
			}

			OnTermination();
		}
	}

	void GameHandler::OnInit()
	{
		#ifdef FORGE_DEBUG_MODE
			// Setup Dear ImGui context
			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO(); (void)io;

			// Setup Dear ImGui style
			ImGui::StyleColorsDark();
			ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
			ImGui_ImplOpenGL3_Init("#version 150");
		#endif // FORGE_DEBUG_MODE
	}

	void GameHandler::OnTermination()
	{
		// glfw: terminate, clearing all previously allocated GLFW resources.
		glfwTerminate();
	}

	bool GameHandler::ShouldTerminate()
	{
		return (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS);
	}
}
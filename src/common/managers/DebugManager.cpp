#include "DebugManager.h"

#include "common/helpers/InputHelper.h"
#include "engine/core/GameHandler.h"
#include "engine/core/ManagerContainer.h"
#include "engine/core/OpenGL.h"
#include "engine/ui/ImGUI.h"

#include <list>

namespace ForgeEngine
{
	DebugManager::DebugManager() :
		m_CurrentDrawMode(GL_FILL)
	{
	}

	bool DebugManager::OnInit() /*override*/
	{
		Mother::OnInit();

		InitImgui();

		return true;
	}

	void DebugManager::InitImgui()
	{
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(GameHandler::m_Window, true);
		ImGui_ImplOpenGL3_Init("#version 150");
	}

	void DebugManager::OnPostUpdate(float dT) /*override*/
	{
		// feed inputs to dear imgui, start new frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ProcessDebugInput();

		// render your GUI
		ImGui::Begin("Framerate");
		ImGui::Text("FPS: %d", ComputeFramerate(dT));
		ImGui::End();

		// Render dear imgui into screen
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	int DebugManager::ComputeFramerate(float dT)
	{
		static std::list<float> deltaTimes;
		float framerate = 0;

		if (deltaTimes.size() == 50)
		{
			deltaTimes.pop_back();
		}
		deltaTimes.push_front(dT);

		for (auto it = deltaTimes.begin(); it != deltaTimes.end(); it++)
		{
			framerate += *it;
		}

		return static_cast<int>(1 / (framerate / deltaTimes.size()));
	}

	void DebugManager::ProcessDebugInput()
	{
		if (InputHelper::IsInputActive(EInputAction::ToggleWireframe))
		{
			ToggleWireframeMode();
		}
	}

	void DebugManager::ToggleWireframeMode()
	{
		int newDrawMode = ((m_CurrentDrawMode == GL_LINE) ? GL_FILL : GL_LINE);
		glPolygonMode(GL_FRONT_AND_BACK, newDrawMode);
		m_CurrentDrawMode = newDrawMode;
	}
}

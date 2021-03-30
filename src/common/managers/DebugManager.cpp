#include "DebugManager.h"

#include "common/helpers/InputHelper.h"
#include "engine/core/ForgeEngine.h"
#include "engine/ui/ImGUI.h"

#include <list>

namespace ForgeEngine
{
	DebugManager::DebugManager() :
		m_CurrentDrawMode(GL_FILL)
	{
	}

	void DebugManager::OnDrawDebug(float dT) /*override*/
	{
		Vector2 mousePosition = InputHelper::GetMousePosition();
		ProcessDebugInput();

		ImGui::Begin("General");
		ImGui::Text("FPS: %d", ComputeFramerate(dT));
		ImGui::Text("Window Size: %d x %d", GameHandler::m_WindowWidth, GameHandler::m_WindowHeight);
		ImGui::Text("Mouse {%d,%d}", static_cast<int>(mousePosition.x), static_cast<int>(mousePosition.y));
		ImGui::End();
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

#include "InputAction.h"

#include "engine/core/GameHandler.h"
#include "engine/core/OpenGL.h"

namespace ForgeEngine
{
	InputAction::InputAction(EInputType type, KeyID id) :
		Mother(),
		m_InputType(type),
		m_Key(id)
	{
	}

	void InputAction::Update(float dT)
	{
		m_Timer.Update(dT);
		switch (m_InputType)
		{
			case (EInputType::Hold):
				m_IsActive = IsKeyPressed();
				break;
			case (EInputType::Press):
				if (!m_Timer.IsStarted())
				{
					if (IsKeyPressed() && !m_NeedsReset)
					{
						m_Timer.Start(K_INPUT_THRESHOLD_MS);
					}
					else
					{
						m_NeedsReset = IsKeyPressed();
						m_IsActive = false;
					}
				}
				else if (m_Timer.IsElapsed())
				{
					m_Timer.Stop();
					m_IsActive = true;
					m_NeedsReset = true;
				}
				break;
			case (EInputType::Release):
				if (IsKeyPressed() && !m_NeedsReset)
				{
					m_NeedsReset = true;
				}
				else if (m_NeedsReset)
				{
					if (!IsKeyPressed())
					{
						m_NeedsReset = false;
						m_IsActive = true;
					}
				}
				else
				{
					m_IsActive = false;
				}
				break;
		}
	}

	bool InputAction::IsKeyPressed() const
	{
		return (glfwGetKey(GameHandler::m_Window, m_Key) == GLFW_PRESS);
	}
}
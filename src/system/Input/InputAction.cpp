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

	bool InputAction::IsKeyPressed() const
	{
		return (glfwGetKey(GameHandler::m_Window, m_Key) == GLFW_PRESS);
	}

	void InputAction::Update(float dT)
	{
		switch (m_InputType)
		{
			case (EInputType::Hold):
				ProcessHoldUpdate();
				break;
			case (EInputType::Press):
				ProcessPressUpdate();
				break;
			case (EInputType::Release):
				ProcessReleaseUpdate();
				break;
		}
	}

	void InputAction::ProcessHoldUpdate()
	{
		m_IsActive = IsKeyPressed();
	}

	void InputAction::ProcessPressUpdate()
	{
		if (IsKeyPressed() && !m_NeedsReset)
		{
			m_NeedsReset = true;
			m_IsActive = true;
		}
		else if (m_NeedsReset)
		{
			m_IsActive = false;
			m_NeedsReset = IsKeyPressed();
		}
	}

	void InputAction::ProcessReleaseUpdate()
	{
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
	}
}
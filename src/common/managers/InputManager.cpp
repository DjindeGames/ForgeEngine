#include "InputManager.h"

#include "engine/core/Game.h"
#include "engine/core/OpenGL.h"

namespace ForgeEngine
{
	InputManager::InputManager() :
		Mother()
	{
		m_InputActionMappings[EInputAction::ToggleWireframe]	= GLFW_KEY_F1;

		m_InputActionMappings[EInputAction::MoveForward]		= GLFW_KEY_W;
		m_InputActionMappings[EInputAction::MoveBackward]		= GLFW_KEY_S;
		m_InputActionMappings[EInputAction::MoveRight]			= GLFW_KEY_D;
		m_InputActionMappings[EInputAction::MoveLeft]			= GLFW_KEY_A;
		m_InputActionMappings[EInputAction::FlyUp]				= GLFW_KEY_UP;
		m_InputActionMappings[EInputAction::FlyDown]			= GLFW_KEY_DOWN;
		m_InputActionMappings[EInputAction::Exit]				= GLFW_KEY_ENTER;
	}

	void InputManager::OnPreUpdate(float dT) /*override*/
	{
		Mother::OnPreUpdate(dT);
		UpdateMousePosition();
	}

	bool InputManager::IsInputActive(EInputAction actionType) const
	{
		auto it = m_InputActionMappings.find(actionType);
		return it != m_InputActionMappings.end()
			&& (glfwGetKey(Game::m_Window,(*it).second) == GLFW_PRESS);
	}

	void InputManager::UpdateMousePosition()
	{
		double x, y;
		glfwGetCursorPos(Game::m_Window, &x, &y);
		m_PreviousMousePosition = m_MousePosition;
		m_MousePosition = Vector2{ x, y };
	}
}
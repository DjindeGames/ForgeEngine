#include "InputManager.h"

#include "engine/core/GameHandler.h"
#include "engine/core/OpenGL.h"

namespace ForgeEngine
{
	InputManager::InputManager() :
		Mother()
	{
		m_InputActionMappings[EInputAction::ToggleWireframe]	= std::unique_ptr<InputAction>(new InputAction{ EInputType::Press, GLFW_KEY_F1 });

		m_InputActionMappings[EInputAction::MoveForward]		= std::unique_ptr<InputAction>(new InputAction{ EInputType::Hold, GLFW_KEY_W });
		m_InputActionMappings[EInputAction::MoveBackward]		= std::unique_ptr<InputAction>(new InputAction{ EInputType::Hold, GLFW_KEY_S });
		m_InputActionMappings[EInputAction::MoveRight]			= std::unique_ptr<InputAction>(new InputAction{ EInputType::Hold, GLFW_KEY_D });
		m_InputActionMappings[EInputAction::MoveLeft]			= std::unique_ptr<InputAction>(new InputAction{ EInputType::Hold, GLFW_KEY_A });
		m_InputActionMappings[EInputAction::FlyUp]				= std::unique_ptr<InputAction>(new InputAction{ EInputType::Hold, GLFW_KEY_UP });
		m_InputActionMappings[EInputAction::FlyDown]			= std::unique_ptr<InputAction>(new InputAction{ EInputType::Hold, GLFW_KEY_DOWN });

		m_InputActionMappings[EInputAction::Exit]				= std::unique_ptr<InputAction>(new InputAction{ EInputType::Release, GLFW_KEY_ENTER });
	}

	void InputManager::OnPreUpdate(float dT) /*override*/
	{
		Mother::OnPreUpdate(dT);
		for (auto& inputAction : m_InputActionMappings)
		{
			inputAction.second.get()->Update(dT);
		}
		UpdateMousePosition();
	}

	bool InputManager::IsInputActive(EInputAction actionType) const
	{
		auto it = m_InputActionMappings.find(actionType);
		return it != m_InputActionMappings.end()
			&& ((*it).second).get()->IsActive();
	}

	void InputManager::UpdateMousePosition()
	{
		double x, y;
		glfwGetCursorPos(GameHandler::m_Window, &x, &y);
		m_PreviousMousePosition = m_MousePosition;
		m_MousePosition = Vector2{ x, y };
	}
}
#include "InputManager.h"

#include "engine/core/ForgeEngine.h"

namespace ForgeEngine
{
	InputManager::InputManager() :
		Mother()
	{
		m_InputActionMappings[EInputAction::ToggleWireframe]	= Unique<InputAction>(new InputAction{ EInputType::Press, EDeviceTarget::Keyboard, GLFW_KEY_F1 });
		m_InputActionMappings[EInputAction::ToggleFreeMouse]	= Unique<InputAction>(new InputAction{ EInputType::Press, EDeviceTarget::Keyboard, GLFW_KEY_F2 });
		m_InputActionMappings[EInputAction::ToggleImGUI]	    = Unique<InputAction>(new InputAction{ EInputType::Press, EDeviceTarget::Keyboard, GLFW_KEY_F3 });
		m_InputActionMappings[EInputAction::RightClickOnce]		= Unique<InputAction>(new InputAction{ EInputType::Press, EDeviceTarget::Mouse, GLFW_MOUSE_BUTTON_RIGHT });
		m_InputActionMappings[EInputAction::LeftClickOnce]		= Unique<InputAction>(new InputAction{ EInputType::Press, EDeviceTarget::Mouse, GLFW_MOUSE_BUTTON_LEFT });

		m_InputActionMappings[EInputAction::MoveForward]		= Unique<InputAction>(new InputAction{ EInputType::Hold, EDeviceTarget::Keyboard, GLFW_KEY_W });
		m_InputActionMappings[EInputAction::MoveBackward]		= Unique<InputAction>(new InputAction{ EInputType::Hold, EDeviceTarget::Keyboard, GLFW_KEY_S });
		m_InputActionMappings[EInputAction::MoveRight]			= Unique<InputAction>(new InputAction{ EInputType::Hold, EDeviceTarget::Keyboard, GLFW_KEY_D });
		m_InputActionMappings[EInputAction::MoveLeft]			= Unique<InputAction>(new InputAction{ EInputType::Hold, EDeviceTarget::Keyboard, GLFW_KEY_A });
		m_InputActionMappings[EInputAction::RightClick]			= Unique<InputAction>(new InputAction{ EInputType::Hold, EDeviceTarget::Mouse, GLFW_MOUSE_BUTTON_RIGHT });
		m_InputActionMappings[EInputAction::LeftClick]			= Unique<InputAction>(new InputAction{ EInputType::Hold, EDeviceTarget::Mouse, GLFW_MOUSE_BUTTON_LEFT });
		m_InputActionMappings[EInputAction::FlyUp]				= Unique<InputAction>(new InputAction{ EInputType::Hold, EDeviceTarget::Keyboard, GLFW_KEY_UP });
		m_InputActionMappings[EInputAction::FlyDown]			= Unique<InputAction>(new InputAction{ EInputType::Hold, EDeviceTarget::Keyboard, GLFW_KEY_DOWN });

		m_InputActionMappings[EInputAction::Exit]				= Unique<InputAction>(new InputAction{ EInputType::Release, EDeviceTarget::Keyboard, GLFW_KEY_ENTER });
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
		glfwGetCursorPos(GameHandler::Get().GetWindow(), &x, &y);
		m_PreviousMousePosition = m_MousePosition;
		m_MousePosition = Vector2{ x, y };
	}
}
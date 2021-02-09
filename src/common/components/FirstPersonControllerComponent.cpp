#include "FirstPersonControllerComponent.h"

#include "common/managers/InputManager.h"

#include "engine/core/Entity.h"
#include "engine/core/Game.h"
#include "engine/core/ManagerContainer.h"
#include "engine/math/Vector4.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace ForgeEngine
{
	FirstPersonControllerComponent::FirstPersonControllerComponent(float moveSpeed /*= 5.f*/, float rotationSpeed /*= 30.f*/) :
		m_MoveSpeed(moveSpeed),
		m_RotationSpeed(rotationSpeed)
	{
	}

	void FirstPersonControllerComponent::OnInit() /*override*/
	{
		Mother::OnInit();
		m_InputManager = ManagerContainer::Get()->GetManagerByType<InputManager>();
	}

	void FirstPersonControllerComponent::OnUpdate(float dT) /*override*/
	{
		Mother::OnUpdate(dT);

		Vector4 translation = VECTOR4_NULL;

		if (m_InputManager->IsInputActive(EInputAction::MoveForward))
		{
			translation.z -= m_MoveSpeed;
		}
		if (m_InputManager->IsInputActive(EInputAction::MoveBackward))
		{
			translation.z += m_MoveSpeed;
		}
		if (m_InputManager->IsInputActive(EInputAction::MoveLeft))
		{
			translation.x -= m_MoveSpeed;
		}
		if (m_InputManager->IsInputActive(EInputAction::MoveRight))
		{
			translation.x += m_MoveSpeed;
		}

		if (m_InputManager->IsInputActive(EInputAction::FlyUp))
		{
			translation.y += m_MoveSpeed;
		}
		if (m_InputManager->IsInputActive(EInputAction::FlyDown))
		{
			translation.y -= m_MoveSpeed;
		}

		//TODO: Normalize translation
		GetOwner()->GetTransform().Translate(translation * dT);
	}
}



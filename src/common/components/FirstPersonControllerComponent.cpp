#include "FirstPersonControllerComponent.h"

#include "common/components/CameraComponent.h"
#include "common/managers/InputManager.h"

#include "engine/core/Entity.h"
#include "engine/core/Game.h"
#include "engine/core/ManagerContainer.h"
#include "engine/math/Vector3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace ForgeEngine
{
	FirstPersonControllerComponent::FirstPersonControllerComponent(float moveSpeed /*= 5.f*/, float rotationSpeed /*= 30.f*/) :
		m_MoveSpeed(moveSpeed),
		m_RotationSpeed(rotationSpeed)
	{
	}

	bool FirstPersonControllerComponent::OnInit() /*override*/
	{
		bool success = Mother::OnInit();
		//ManagerContainer::Get()->GetManager(m_InputManager);
		m_InputManager = ManagerContainer::Get()->GetManagerByType<InputManager>();
		m_CameraComponent = GetOwner()->GetComponentByType<CameraComponent>();
		//GetOwner()->GetComponent(m_CameraComponent);
		glfwSetInputMode(Game::m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		return success
			&& m_InputManager != nullptr
			&& m_CameraComponent != nullptr;
	}

	void FirstPersonControllerComponent::OnUpdate(float dT) /*override*/
	{
		Mother::OnUpdate(dT);

		Vector3 translation = VECTOR3_NULL;

		if (m_InputManager->IsInputActive(EInputAction::MoveForward))
		{
			translation += m_MoveSpeed * m_CameraComponent->GetSight();
		}
		if (m_InputManager->IsInputActive(EInputAction::MoveBackward))
		{
			translation -= m_MoveSpeed * m_CameraComponent->GetSight();
		}
		if (m_InputManager->IsInputActive(EInputAction::MoveLeft))
		{
			translation += m_MoveSpeed * m_CameraComponent->GetRight();
		}
		if (m_InputManager->IsInputActive(EInputAction::MoveRight))
		{
			translation -= m_MoveSpeed * m_CameraComponent->GetRight();
		}

		if (m_InputManager->IsInputActive(EInputAction::FlyUp))
		{
			translation += m_MoveSpeed * VECTOR3_Y;
		}
		if (m_InputManager->IsInputActive(EInputAction::FlyDown))
		{
			translation -= m_MoveSpeed * VECTOR3_Y;
		}

		Vector2 mouseVelocity = m_InputManager->GetMouseVelocity();
		m_CameraComponent->SetYaw(m_CameraComponent->GetYaw() - (mouseVelocity.x * m_RotationSpeed * dT));
		m_CameraComponent->SetPitch(m_CameraComponent->GetPitch() + (mouseVelocity.y * m_RotationSpeed * dT));

		//TODO: Normalize translation
		GetOwner()->GetTransform().Translate(translation * dT);
	}
}



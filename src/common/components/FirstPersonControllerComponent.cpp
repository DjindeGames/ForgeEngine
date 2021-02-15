#include "FirstPersonControllerComponent.h"

#include "common/components/CameraComponent.h"
#include "common/managers/InputManager.h"

#include "engine/core/Entity.h"
#include "engine/core/Game.h"
#include "engine/core/ManagerContainer.h"
#include "system/math/MathUtils.h"
#include "system/math/Vector3.h"

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

		m_InputManager = ManagerContainer::Get()->GetManagerByType<InputManager>();
		m_CameraComponent = GetOwner()->GetComponentByType<CameraComponent>();
		glfwSetInputMode(Game::m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		return success
			&& m_InputManager != nullptr
			&& m_CameraComponent != nullptr;
	}

	void FirstPersonControllerComponent::OnUpdate(float dT) /*override*/
	{
		Mother::OnUpdate(dT);

		Vector3 translation = VECTOR3_NULL;
		Vector2 mouseVelocity = m_InputManager->GetMouseVelocity();
		float yaw = m_CameraComponent->GetYaw() - (mouseVelocity.x * m_RotationSpeed * dT);
		float pitch = ForgeMaths::Clamp(m_CameraComponent->GetPitch() + (mouseVelocity.y * m_RotationSpeed * dT), -89.f, 89.f);

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

		m_CameraComponent->SetYaw(yaw);
		m_CameraComponent->SetPitch(pitch);

		//TODO: Normalize translation
		GetOwner()->GetTransform().Translate(translation * dT);
	}

	void FirstPersonControllerComponent::OnDestroy() /*override*/
	{
		Mother::OnDestroy();
		glfwSetInputMode(Game::m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}



#include "FirstPersonControllerComponent.h"

#include "common/components/CameraComponent.h"
#include "common/helpers/InputHelper.h"
#include "engine/core/ForgeEngine.h"
#include "system/math/MathUtils.h"
#include "system/math/Vector3.h"

namespace ForgeEngine
{
	FirstPersonControllerComponent::FirstPersonControllerComponent(float moveSpeed /*= 10.f*/, float rotationSpeed /*= 10.f*/) 
        : Component()
		, m_MoveSpeed(moveSpeed)
		, m_RotationSpeed(rotationSpeed)
	{
	}

	bool FirstPersonControllerComponent::OnInit() /*override*/
	{
		bool success = Mother::OnInit();

		m_CameraComponent = GetOwner()->GetComponentByType<CameraComponent>();
		glfwSetInputMode(GameHandler::Get().GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		return success
			&& m_CameraComponent != nullptr;
	}

	void FirstPersonControllerComponent::OnUpdate(float dT) /*override*/
	{
		Mother::OnUpdate(dT);

		Vector3 translation = VECTOR3_NULL;
		Vector2 mouseVelocity = InputHelper::GetMouseVelocity();
		float yaw = m_CameraComponent->GetYaw() - (mouseVelocity.x * m_RotationSpeed * dT);
		float pitch = ForgeMaths::Clamp(m_CameraComponent->GetPitch() + (mouseVelocity.y * m_RotationSpeed * dT), -89.f, 89.f);

        Vector3 sight = m_CameraComponent->GetSight();
        sight = Vector3(sight.x, 0.f, sight.z);

		if (InputHelper::IsInputActive(EInputAction::MoveForward))
		{
			translation += m_MoveSpeed * sight;
		}
		if (InputHelper::IsInputActive(EInputAction::MoveBackward))
		{
			translation -= m_MoveSpeed * sight;
		}
		if (InputHelper::IsInputActive(EInputAction::MoveLeft))
		{
			translation += m_MoveSpeed * m_CameraComponent->GetRight();
		}
		if (InputHelper::IsInputActive(EInputAction::MoveRight))
		{
			translation -= m_MoveSpeed * m_CameraComponent->GetRight();
		}

		if (InputHelper::IsInputActive(EInputAction::FlyUp))
		{
			translation += m_MoveSpeed * VECTOR3_UP;
		}
		if (InputHelper::IsInputActive(EInputAction::FlyDown))
		{
			translation -= m_MoveSpeed * VECTOR3_UP;
		}

		m_CameraComponent->SetYaw(yaw);
		m_CameraComponent->SetPitch(pitch);

		//TODO: Normalize translation
        glm::normalize(translation);
		GetOwner()->GetTransform().Translate(translation * dT);
	}

	void FirstPersonControllerComponent::OnDestroy() /*override*/
	{
		glfwSetInputMode(GameHandler::Get().GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		Mother::OnDestroy();
	}
}



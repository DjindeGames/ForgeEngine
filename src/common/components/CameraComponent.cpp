#include "CameraComponent.h"

#include "system/math/MathUtils.h"

#include <glm/gtc/matrix_transform.hpp>

namespace ForgeEngine
{
	/*static*/ const CameraComponent* CameraComponent::s_ActiveCamera{};

	CameraComponent::CameraComponent(float fov /*= 45.f*/, float aspectRatio /*= 16.f / 9.f*/, float nearPlane /*= 0.1f*/, float farPlane /*= 100.f*/) :
		Mother()
	{
		m_Projection = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
		s_ActiveCamera = this;
	}

	void CameraComponent::OnUpdate(float dT) /*override*/
	{
		Mother::OnUpdate(dT);
		RefreshView();
	}

	void CameraComponent::OnActivate() /*override*/
	{
		Mother::OnActivate();
		s_ActiveCamera = this;
	}

	void CameraComponent::OnDeactivate() /*override*/
	{
		Mother::OnDeactivate();
		ClearActiveCameraIfNeeded();
	}

	void CameraComponent::OnDestroy() /*override*/
	{
		Mother::OnDestroy();
		ClearActiveCameraIfNeeded();
	}

	void CameraComponent::ClearActiveCameraIfNeeded() /*override*/
	{
		if (s_ActiveCamera == this)
		{
			s_ActiveCamera = nullptr;
		}
	}

	void CameraComponent::RefreshView()
	{
		m_View = Matrix4{ 1.f };
		ForgeMaths::Translate(m_View, -GetOwner()->GetPosition());

		Vector3 sight{};
		if (m_IsFocusActive && m_FocusedEntity != nullptr)
		{
			sight = m_FocusedEntity->GetPosition() - GetOwner()->GetPosition();
		}
		else
		{
			sight = ForgeMaths::ComputeCameraSight(m_Yaw, m_Pitch);
		}

		m_Sight = glm::normalize(sight);
		m_Right = ForgeMaths::Cross(VECTOR3_Y, m_Sight);
		m_Up = ForgeMaths::Cross(m_Sight, m_Right);

		ForgeMaths::LookAt(m_View, GetOwner()->GetPosition(), GetOwner()->GetPosition() + m_Sight, VECTOR3_Y);
	}
}
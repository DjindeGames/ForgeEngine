#include "CameraComponent.h"

#include "glm/ext/matrix_clip_space.hpp" 

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
		m_View = Matrix4{1.f};
		ForgeMaths::Translate(m_View, -GetOwner()->GetPosition());
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
}
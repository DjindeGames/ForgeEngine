#include "CameraComponent.h"

#include "glm/ext/matrix_clip_space.hpp" 

namespace ForgeEngine
{
	/*static*/ const CameraComponent* CameraComponent::s_ActiveCamera{};

	CameraComponent::CameraComponent(float fov /*= 45.f*/, float aspectRatio /*= 16.f / 9.f*/, float nearPlane /*= 0.1f*/, float farPlane /*= 100.f*/)
	{
		m_Projection = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
		s_ActiveCamera = this;
	}

	void CameraComponent::OnUpdate(float dT) /*override*/
	{
		m_Projection = Matrix4{0.f};
		m_Projection = DoTranslate(m_Projection, -GetOwner()->GetPosition());
	}

	void CameraComponent::OnActivate() /*override*/
	{
		s_ActiveCamera = this;
	}

	void CameraComponent::OnDeactivate() /*override*/
	{
		ClearActiveCameraIfNeeded();
	}

	void CameraComponent::OnDestroy() /*override*/
	{
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
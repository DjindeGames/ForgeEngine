#include "ViewerComponent.h"

#include "engine/core/Game.h"
#include "engine/math/Math.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace ForgeEngine
{
	ViewerComponent::ViewerComponent(float rotationSpeed) :
		m_RotationSpeed(rotationSpeed)
	{

	}

	void ViewerComponent::OnInit()
	{
		m_InitialTransform = GetOwner()->GetTransform();
	}

	void ViewerComponent::OnUpdate(float dT) /*override*/
	{
		Vector3 eulerRotation{};
		Vector3 translation{};
		
		if (glfwGetKey(Game::m_Window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			eulerRotation.y += m_RotationSpeed;
		}
		if (glfwGetKey(Game::m_Window, GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			eulerRotation.y -= m_RotationSpeed;
		}
		if (glfwGetKey(Game::m_Window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			eulerRotation.x -= m_RotationSpeed;
		}
		if (glfwGetKey(Game::m_Window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			eulerRotation.x += m_RotationSpeed;
		}

		if (glfwGetKey(Game::m_Window, GLFW_KEY_Z) == GLFW_PRESS)
		{
			translation += VECTOR3_Y;
		}
		if (glfwGetKey(Game::m_Window, GLFW_KEY_S) == GLFW_PRESS)
		{
			translation -= VECTOR3_Y;
		}
		if (glfwGetKey(Game::m_Window, GLFW_KEY_Q) == GLFW_PRESS)
		{
			translation += VECTOR3_X;
		}
		if (glfwGetKey(Game::m_Window, GLFW_KEY_D) == GLFW_PRESS)
		{
			translation -= VECTOR3_X;
		}

		if (glfwGetKey(Game::m_Window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			ResetRotation();
		}

		m_Owner->GetTransform().Rotate(eulerRotation * dT);
		m_Owner->GetTransform().Translate(translation * dT);
	}

	void ViewerComponent::ResetRotation()
	{
		m_Owner->SetTransform(m_InitialTransform);
	}
}
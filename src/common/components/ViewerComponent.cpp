#include "ViewerComponent.h"

#include "engine/core/Game.h"
#include "engine/math/Math.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace ForgeEngine
{
	ViewerComponent::ViewerComponent(float translationSpeed, float rotationSpeed, float scaleSpeed) :
		m_TranslationSpeed(translationSpeed),
		m_RotationSpeed(rotationSpeed),
		m_ScaleSpeed(scaleSpeed)
	{
	}

	void ViewerComponent::OnInit()
	{
		m_InitialTransform = GetOwner()->GetTransform();
	}

	void ViewerComponent::OnUpdate(float dT) /*override*/
	{
		//Reset
		if (glfwGetKey(Game::m_Window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			ResetTransform();
			return;
		}

		Vector3 eulerRotation{};
		Vector3 translation{};
		Vector3 scale{ 1.f };

		//Translation
		if (glfwGetKey(Game::m_Window, GLFW_KEY_W) == GLFW_PRESS)
		{
			translation.y += m_TranslationSpeed;
		}
		if (glfwGetKey(Game::m_Window, GLFW_KEY_S) == GLFW_PRESS)
		{
			translation.y -= m_TranslationSpeed;
		}
		if (glfwGetKey(Game::m_Window, GLFW_KEY_A) == GLFW_PRESS)
		{
			translation.x -= m_TranslationSpeed;
		}
		if (glfwGetKey(Game::m_Window, GLFW_KEY_D) == GLFW_PRESS)
		{
			translation.x += m_TranslationSpeed;
		}

		//Rotation
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

		//Scale
		if (glfwGetKey(Game::m_Window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS)
		{
			scale *= (1.f / m_ScaleSpeed);
		}
		if (glfwGetKey(Game::m_Window, GLFW_KEY_KP_ADD) == GLFW_PRESS)
		{
			scale *= m_ScaleSpeed;
		}

		m_Owner->GetTransform().Rotate(eulerRotation * dT);
		m_Owner->GetTransform().Translate(translation * dT);
		m_Owner->GetTransform().Scale(scale);
	}

	void ViewerComponent::ResetTransform()
	{
		m_Owner->SetTransform(m_InitialTransform);
	}
}
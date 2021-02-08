#include "FirstPersonControllerComponent.h"

#include "engine/core/Entity.h"
#include "engine/core/Game.h"
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

	void FirstPersonControllerComponent::OnUpdate(float dT) /*override*/
	{
		Mother::OnUpdate(dT);

		Vector4 translation = VECTOR4_NULL;

		//Translation
		if (glfwGetKey(Game::m_Window, GLFW_KEY_W) == GLFW_PRESS)
		{
			translation.z -= m_MoveSpeed;
		}
		if (glfwGetKey(Game::m_Window, GLFW_KEY_S) == GLFW_PRESS)
		{
			translation.z += m_MoveSpeed;
		}
		if (glfwGetKey(Game::m_Window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			translation.y += m_MoveSpeed;
		}
		if (glfwGetKey(Game::m_Window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			translation.y -= m_MoveSpeed;
		}
		if (glfwGetKey(Game::m_Window, GLFW_KEY_A) == GLFW_PRESS)
		{
			translation.x -= m_MoveSpeed;
		}
		if (glfwGetKey(Game::m_Window, GLFW_KEY_D) == GLFW_PRESS)
		{
			translation.x += m_MoveSpeed;
		}

		GetOwner()->GetTransform().Translate(translation * dT);
	}
}



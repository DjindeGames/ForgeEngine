#include "Math.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace ForgeEngine
{
	Matrix4 DoTranslate(const Matrix4& matrix, const Vector3& direction)
	{
		return glm::translate(matrix, direction);
	}

	Matrix4 DoRotate(const Matrix4& matrix, float angle, const Vector3& axis)
	{
		return glm::rotate(matrix, glm::radians(angle), axis);
	}

	Matrix4 DoScale(const Matrix4& matrix, const Vector3& scale)
	{
		return glm::scale(matrix, scale);
	}

	void Decompose(const Matrix4& matrix, Vector3& position, Vector3& rotation, Vector3& scale)
	{
		glm::quat quaternion;
		Vector3 skew;
		Vector4 perspective;
		glm::decompose(matrix, scale, quaternion, position, skew, perspective);
		rotation = glm::eulerAngles(quaternion);
	}
}
#include "Matrix4.h"

#include "Vector3.h"

#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace ForgeEngine
{
	Matrix4 DoTranslate(const Matrix4& matrix, const Vector4& direction)
	{
		return glm::translate(matrix, Vector3(direction));
	}

	Matrix4 DoRotate(const Matrix4& matrix, float angle, const Vector4& axis)
	{
		return glm::rotate(matrix, glm::radians(angle), Vector3(axis));
	}

	Matrix4 DoScale(const Matrix4& matrix, const Vector4& scale)
	{
		return glm::scale(matrix, Vector3(scale));
	}

	void Decompose(const Matrix4& matrix, Vector4& position, Vector4& rotation, Vector4& scale)
	{
		glm::quat quaternion;
		Vector3 position3;
		Vector3 scale3;
		Vector3 skew;
		Vector4 perspective;

		glm::decompose(matrix, scale3, quaternion, position3, skew, perspective);

		Vector3 rotation3 = glm::eulerAngles(quaternion);

		position = Vector4(position3.x, position3.y, position3.z, 0.f);
		rotation = Vector4(rotation3.x, rotation3.y, rotation3.z, 0.f);
		scale = Vector4(scale3.x, scale3.y, scale3.z, 0.f);
	}
}
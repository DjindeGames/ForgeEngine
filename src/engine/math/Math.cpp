#include "Math.h"

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
}
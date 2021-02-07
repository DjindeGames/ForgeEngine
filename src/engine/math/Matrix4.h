#pragma once

#include "Vector4.h"

#include "glm/mat4x4.hpp"

namespace ForgeEngine
{
	typedef glm::mat4x4 Matrix4;

	Matrix4 DoTranslate(const Matrix4& matrix, const Vector4& direction);
	Matrix4 DoRotate(const Matrix4& matrix, float angle, const Vector4& axis);
	Matrix4 DoScale(const Matrix4& matrix, const Vector4& scale);

	void Decompose(const Matrix4& matrix, Vector4& position, Vector4& rotation, Vector4& scale);
}
#pragma once

#include "Vector4.h"

#include "glm/mat4x4.hpp"

namespace ForgeEngine
{
	typedef glm::mat4x4 Matrix4;

	namespace ForgeMaths
	{
		void Translate(Matrix4& matrix, const Vector4& direction);
		void Rotate(Matrix4& matrix, float angle, const Vector4& axis);
		void Rotate(Matrix4& matrix, const Vector4& eulerAngles);
		void Scale(Matrix4& matrix, const Vector4& scale);

		void Decompose(const Matrix4& matrix, Vector4& position, Vector4& rotation, Vector4& scale);
	}
}
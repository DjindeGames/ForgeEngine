#include "Matrix4.h"

#include "Vector3.h"

#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace ForgeEngine
{
	namespace ForgeMaths
	{
		void Translate(Matrix4& matrix, const Vector4& direction)
		{
			matrix = glm::translate(matrix, Vector3(direction));
		}

		void Rotate(Matrix4& matrix, float angle, const Vector4& axis)
		{
			matrix = glm::rotate(matrix, glm::radians(angle), Vector3(axis));
		}

		void Rotate(Matrix4& matrix, const Vector4& eulerAngles)
		{
			Rotate(matrix, eulerAngles.x, VECTOR4_X);
			Rotate(matrix, eulerAngles.y, VECTOR4_Y);
			Rotate(matrix, eulerAngles.z, VECTOR4_Z);
		}

		void Scale(Matrix4& matrix, const Vector4& scale)
		{
			matrix = glm::scale(matrix, Vector3(scale));
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
}
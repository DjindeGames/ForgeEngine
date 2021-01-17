#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace ForgeEngine
{
	//TODO : FIND A SOLUTION TO AVOID INCLUDING THIS HEADER JUST TO FORWARD DECLARE THE FOLLOWING TYPES!!
	typedef glm::vec3 Vector3;
	typedef glm::mat4 Matrix4;

	#define VECTOR3_X Vector3(1.f, 0.f, 0.f)
	#define VECTOR3_Y Vector3(0.f, 1.f, 0.f)
	#define VECTOR3_Z Vector3(0.f, 0.f, 1.f)

	#define VECTOR3_UNIT Vector3(1.f, 1.f, 1.f)

	Matrix4 DoTranslate(const Matrix4& matrix, const Vector3& direction);
	Matrix4 DoRotate(const Matrix4& matrix, float angle, const Vector3& axis);
	Matrix4 DoScale(const Matrix4& matrix, const Vector3& scale);
}
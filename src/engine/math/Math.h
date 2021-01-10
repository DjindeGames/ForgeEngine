#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace ForgeEngine
{
	//TODO : FIND A SOLUTION TO AVOID INCLUDING THIS HEADER JUST TO FORWARD DECLARE THE FOLLOWING TYPES!!
	typedef glm::vec3 Vector3;
	typedef glm::mat4 Matrix4;

	Matrix4 DoTranslate(const Matrix4& matrix, const Vector3& direction);
	Matrix4 DoRotate(const Matrix4& matrix, float angle, const Vector3& axis);
}
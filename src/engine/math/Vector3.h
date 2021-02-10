#pragma once

#include "glm/vec3.hpp"

namespace ForgeEngine
{
	#define VECTOR3_X Vector3(1.f, 0.f, 0.f)
	#define VECTOR3_Y Vector3(0.f, 1.f, 0.f)
	#define VECTOR3_Z Vector3(0.f, 0.f, 1.f)

	#define VECTOR3_UNIT Vector3(1.f, 1.f, 1.f)
	#define VECTOR3_NULL Vector3(0.f, 0.f, 0.f)

	typedef glm::vec3 Vector3;

	namespace ForgeMaths
	{
		Vector3 Cross(const Vector3& v1, const Vector3& v2);
	}
}
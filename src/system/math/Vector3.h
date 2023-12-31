#pragma once

#include "glm/vec3.hpp"

namespace ForgeEngine
{
	#define VECTOR3_SIDE Vector3(1.f, 0.f, 0.f)
	#define VECTOR3_UP Vector3(0.f, 1.f, 0.f)
	#define VECTOR3_FORWARD Vector3(0.f, 0.f, 1.f)

	#define VECTOR3_UNIT Vector3(1.f, 1.f, 1.f)
	#define VECTOR3_NULL Vector3(0.f, 0.f, 0.f)

	typedef glm::vec3 Vector3;

	namespace ForgeMaths
	{
		Vector3 Flatten(const Vector3& v);
		Vector3 FlattenAndNormalize(const Vector3& v);
		Vector3 Cross(const Vector3& v1, const Vector3& v2);
		Vector3 Normalize(const Vector3& v);
		float Dot(const Vector3& v1, const Vector3& v2);
		float Distance(const Vector3& v1, const Vector3& v2);
	}
}
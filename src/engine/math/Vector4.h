#pragma once

#include "glm/vec4.hpp"

namespace ForgeEngine
{
	#define VECTOR4_X Vector4(1.f, 0.f, 0.f, 0.f)
	#define VECTOR4_Y Vector4(0.f, 1.f, 0.f, 0.f)
	#define VECTOR4_Z Vector4(0.f, 0.f, 1.f, 0.f)

	#define VECTOR4_UNIT Vector4(1.f, 1.f, 1.f, 0.f)
	#define VECTOR4_NULL Vector4(0.f, 0.f, 0.f, 0.f)

	typedef glm::vec4 Vector4;
}
#include "Vector3.h"

#include <glm/gtc/matrix_transform.hpp>

namespace ForgeEngine
{
	namespace ForgeMaths
	{
		Vector3 Cross(const Vector3& v1, const Vector3& v2)
		{
			return glm::cross(v1, v2);
		}

        float Dot(const Vector3& v1, const Vector3& v2)
        {
            return glm::dot(v1, v2);
        }

        float Distance(const Vector3& v1, const Vector3& v2)
        {
            return (v1 - v2).length();
        }
	}
}
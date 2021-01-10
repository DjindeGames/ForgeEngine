#include "Transform.h"

namespace ForgeEngine
{
	Transform::Transform() : m_Matrix{1}
	{
	}

	void Transform::Translate(const Vector3& vector)
	{
		m_Matrix = DoTranslate(m_Matrix, vector);
	}

	void Transform::Rotate(float angle, const Vector3& axis)
	{
		m_Matrix = DoRotate(m_Matrix, angle, axis);
	}
}
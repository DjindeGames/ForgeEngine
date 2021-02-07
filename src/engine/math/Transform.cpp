#include "Transform.h"

namespace ForgeEngine
{
	Transform::Transform() : m_Matrix{1}
	{
	}

	void Transform::Reset()
	{
		m_Matrix = Matrix4{1};
	}

	void Transform::SetPosition(const Vector4& position)
	{
		m_Matrix[3][0] = position.x;
		m_Matrix[3][1] = position.y;
		m_Matrix[3][2] = position.z;
	}

	void Transform::SetRotation(const Vector4& rotation)
	{
	}

	void Transform::SetScale(const Vector4& scale)
	{
	}

	void Transform::Translate(const Vector4& vector)
	{
		m_Matrix = DoTranslate(m_Matrix, vector);
	}

	void Transform::Rotate(float angle, const Vector4& axis)
	{
		m_Matrix = DoRotate(m_Matrix, angle, axis);
	}

	void Transform::Rotate(const Vector4& euleurAngles)
	{
		Rotate(euleurAngles.x, VECTOR4_X);
		Rotate(euleurAngles.y, VECTOR4_Y);
		Rotate(euleurAngles.z, VECTOR4_Z);
	}

	void Transform::Scale(const Vector4& scale)
	{
		m_Matrix = DoScale(m_Matrix, scale);
	}

	void Transform::Refresh()
	{
		Decompose(m_Matrix, m_Position, m_Rotation, m_Scale);
	}
}
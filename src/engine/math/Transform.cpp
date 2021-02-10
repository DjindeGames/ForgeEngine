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

	void Transform::SetPosition(const Vector3& position)
	{
		m_Matrix[3][0] = position.x;
		m_Matrix[3][1] = position.y;
		m_Matrix[3][2] = position.z;
	}

	void Transform::SetRotation(const Vector3& rotation)
	{
	}

	void Transform::SetScale(const Vector3& scale)
	{
	}

	void Transform::Translate(const Vector3& vector)
	{
		ForgeMaths::Translate(m_Matrix, vector);
	}

	void Transform::Rotate(float angle, const Vector3& axis)
	{
		ForgeMaths::Rotate(m_Matrix, angle, axis);
	}

	void Transform::Rotate(const Vector3& euleurAngles)
	{
		Rotate(euleurAngles.x, VECTOR3_X);
		Rotate(euleurAngles.y, VECTOR3_Y);
		Rotate(euleurAngles.z, VECTOR3_Z);
	}

	void Transform::Scale(const Vector3& scale)
	{
		ForgeMaths::Scale(m_Matrix, scale);
	}

	void Transform::Refresh()
	{
		ForgeMaths::Decompose(m_Matrix, m_Position, m_Rotation, m_Scale);
	}
}
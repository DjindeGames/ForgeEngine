#include "Transform.h"

namespace ForgeEngine
{
	Transform::Transform() : m_Matrix{1}
	{
	}

	void Transform::Reset()
	{
		m_Matrix = Matrix4{1};
		Refresh();
	}

	void Transform::SetPosition(const Vector3& position)
	{
		m_Matrix[3][0] = position.x;
		m_Matrix[3][1] = position.y;
		m_Matrix[3][2] = position.z;
		Refresh();
	}

	void Transform::SetRotation(const Vector3& rotation)
	{
		Refresh();
	}

	void Transform::SetScale(const Vector3& scale)
	{
		Refresh();
	}

	void Transform::Translate(const Vector3& vector)
	{
		m_Matrix = DoTranslate(m_Matrix, vector);
		Refresh();
	}

	void Transform::Rotate(float angle, const Vector3& axis)
	{
		m_Matrix = DoRotate(m_Matrix, angle, axis);
		Refresh();
	}

	void Transform::Rotate(const Vector3& euleurAngles)
	{
		Rotate(euleurAngles.x, VECTOR3_X);
		Rotate(euleurAngles.y, VECTOR3_Y);
		Rotate(euleurAngles.z, VECTOR3_Z);
		Refresh();
	}

	void Transform::Scale(const Vector3& scale)
	{
		m_Matrix = DoScale(m_Matrix, scale);
		Refresh();
	}

	void Transform::Refresh()
	{
		Decompose(m_Matrix, m_Position, m_Rotation, m_Scale);
	}
}
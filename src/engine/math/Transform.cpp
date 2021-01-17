#include "Transform.h"

namespace ForgeEngine
{
	Transform::Transform() : m_Matrix{1}
	{
	}

	Vector3 Transform::GetPosition() const
	{
		return Vector3{ 
			m_Matrix[0][3], 
			m_Matrix[1][3],
			m_Matrix[1][3] 
		};
	}

	Vector3 Transform::GetRotation() const
	{
		return glm::eulerAngles(glm::quat{ m_Matrix });
	}

	Vector3 Transform::GetScale() const
	{
		return Vector3{ 
			Vector3{m_Matrix[0][0], m_Matrix[1][0], m_Matrix[2][0]}.length(),
			Vector3{m_Matrix[0][1], m_Matrix[1][1], m_Matrix[2][1]}.length(),
			Vector3{m_Matrix[0][2], m_Matrix[1][2], m_Matrix[2][2]}.length(),
		};
	}

	void Transform::SetPosition(const Vector3& position)
	{
		m_Matrix[0][3] = position.x;
		m_Matrix[1][3] = position.y;
		m_Matrix[1][3] = position.z;
	}

	void Transform::SetRotation(const Vector3& rotation)
	{

	}

	void Transform::SetScale(const Vector3& scale)
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

	void Transform::Rotate(const Vector3& euleurAngles)
	{
		Rotate(euleurAngles.x, VECTOR3_X);
		Rotate(euleurAngles.y, VECTOR3_Y);
		Rotate(euleurAngles.z, VECTOR3_Z);
	}

	void Transform::Scale(const Vector3& scale)
	{
		m_Matrix = DoScale(m_Matrix, scale);
	}
}
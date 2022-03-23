#include "TransformComponent.h"

namespace ForgeEngine
{
	TransformComponent::TransformComponent() : 
		Mother{},
		m_Matrix{1}
	{
	}

	void TransformComponent::OnPostUpdate(float dT) /*override*/
	{
		ForgeMaths::Decompose(m_Matrix, m_Position, m_Rotation, m_Scale);
	}

	void TransformComponent::Reset()
	{
		m_Matrix = Matrix4{1};
	}

	void TransformComponent::SetPosition(const Vector3& position)
	{
		m_Matrix[3][0] = position.x;
		m_Matrix[3][1] = position.y;
		m_Matrix[3][2] = position.z;
	}

	void TransformComponent::SetRotation(const Vector3& rotation)
	{
	}

	void TransformComponent::SetScale(const Vector3& scale)
	{
	}

	void TransformComponent::Translate(const Vector3& vector)
	{
		ForgeMaths::Translate(m_Matrix, vector);
	}

	void TransformComponent::Rotate(float angle, const Vector3& axis)
	{
		ForgeMaths::Rotate(m_Matrix, angle, axis);
	}

	void TransformComponent::Rotate(const Vector3& euleurAngles)
	{
		Rotate(euleurAngles.x, VECTOR3_X);
		Rotate(euleurAngles.y, VECTOR3_Y);
		Rotate(euleurAngles.z, VECTOR3_Z);
	}

	void TransformComponent::Scale(const Vector3& scale)
	{
		ForgeMaths::Scale(m_Matrix, scale);
	}
}
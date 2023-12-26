#include "TransformComponent.h"

namespace ForgeEngine
{
	TransformComponent::TransformComponent() : 
		Mother{},
		m_Matrix{1}
	{
	}

    Vector3 TransformComponent::GetPosition() const 
    { 
        if (m_Dirty)
        {
            ForgeMaths::Decompose(m_Matrix, m_Position, m_Rotation, m_Scale);
            m_Dirty = false;
        }
        return m_Position; 
    }

    Vector3 TransformComponent::GetRotation() const 
    { 
        if (m_Dirty)
        {
            ForgeMaths::Decompose(m_Matrix, m_Position, m_Rotation, m_Scale);
            m_Dirty = false;
        }
        return m_Rotation; 
    }

    Vector3 TransformComponent::GetScale() const 
    { 
        if (m_Dirty)
        {
            ForgeMaths::Decompose(m_Matrix, m_Position, m_Rotation, m_Scale);
            m_Dirty = false;
        }
        return m_Scale; 
    }

	void TransformComponent::Reset()
	{
		m_Matrix = Matrix4{1};
        m_Dirty = true;
	}

	void TransformComponent::SetPosition(const Vector3& position)
	{
		m_Matrix[3][0] = position.x;
		m_Matrix[3][1] = position.y;
		m_Matrix[3][2] = position.z;
        m_Dirty = true;
	}

	void TransformComponent::SetRotation(const Vector3& rotation)
	{
        m_Dirty = true;
	}

	void TransformComponent::SetScale(const Vector3& scale)
	{
        m_Dirty = true;
	}

	void TransformComponent::Translate(const Vector3& vector)
	{
		ForgeMaths::Translate(m_Matrix, vector);
        m_Dirty = true;
	}

	void TransformComponent::Rotate(float angle, const Vector3& axis)
	{
		ForgeMaths::Rotate(m_Matrix, angle, axis);
        m_Dirty = true;
	}

	void TransformComponent::Rotate(const Vector3& euleurAngles)
	{
		Rotate(euleurAngles.x, VECTOR3_X);
		Rotate(euleurAngles.y, VECTOR3_Y);
		Rotate(euleurAngles.z, VECTOR3_Z);
        m_Dirty = true;
	}

	void TransformComponent::Scale(const Vector3& scale)
	{
		ForgeMaths::Scale(m_Matrix, scale);
        m_Dirty = true;
	}
}
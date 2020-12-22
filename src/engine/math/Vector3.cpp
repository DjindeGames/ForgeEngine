#include "Vector3.h"

#include <cmath>
#include <type_traits>
#include <stdexcept>

namespace ForgeEngine
{
	Vector3::Vector3(float x, float y, float z) : 
		m_X(x), 
		m_Y(y), 
		m_Z(z)
	{
	}

	/*static*/ float Vector3::Distance(const Vector3& v1, const Vector3& v2)
	{
		return v1.Distance(v2);
	}

	float Vector3::Distance(const Vector3& other) const
	{
		return (
			sqrt(
				pow(other.GetX() - m_X, 2) + 
				pow(other.GetY() - m_Y, 2) +
				pow(other.GetZ() - m_Z, 2)
			)
		);
	}

	float Vector3::GetLength() const
	{
		return (
			sqrt(
				pow(m_X, 2) + 
				pow(m_Y, 2) + 
				pow(m_Z, 2)
			)
		);
	}

	const Vector3 Vector3::GetNormalized() const
	{
		return (Vector3(*this) / GetLength());
	}

	Vector3 Vector3::operator/(const Vector3& other) 
	{
		return Vector3{ m_X / other.GetX() , m_Y / other.GetY() , m_Z / other.GetZ() };
	}

	Vector3& Vector3::operator/=(const Vector3& other)
	{
		m_X /= other.GetX();
		m_Y /= other.GetY();
		m_Z /= other.GetZ();
		return (*this);
	}

	Vector3 Vector3::operator*(const Vector3& other)
	{
		return Vector3{ m_X * other.GetX() , m_Y * other.GetY() , m_Z * other.GetZ() };
	}

	Vector3& Vector3::operator*=(const Vector3& other)
	{
		m_X *= other.GetX();
		m_Y *= other.GetY();
		m_Z *= other.GetZ();
		return (*this);
	}

	Vector3 Vector3::operator+(const Vector3& other)
	{
		return Vector3{ m_X + other.GetX() , m_Y + other.GetY() , m_Z + other.GetZ() };
	}

	Vector3& Vector3::operator+=(const Vector3& other)
	{
		m_X += other.GetX();
		m_Y += other.GetY();
		m_Z += other.GetZ();
		return (*this);
	}

	Vector3 Vector3::operator-(const Vector3& other)
	{
		return Vector3{ m_X - other.GetX() , m_Y - other.GetY() , m_Z - other.GetZ() };
	}

	Vector3& Vector3::operator-=(const Vector3& other)
	{
		m_X -= other.GetX();
		m_Y -= other.GetY();
		m_Z -= other.GetZ();
		return (*this);
	}

	Vector3 Vector3::operator/(float other)
	{
		return Vector3{ m_X / other , m_Y / other , m_Z / other };
	}

	Vector3& Vector3::operator/=(float other)
	{
		m_X /= other;
		m_Y /= other;
		m_Z /= other;
		return (*this);
	}

	Vector3 Vector3::operator*(float other)
	{
		return Vector3{ m_X * other , m_Y * other , m_Z * other };
	}

	Vector3& Vector3::operator*=(float other)
	{
		m_X *= other;
		m_Y *= other;
		m_Z *= other;
		return (*this);
	}

	Vector3 Vector3::operator+(float other)
	{
		return Vector3{ m_X + other , m_Y + other , m_Z + other };
	}

	Vector3& Vector3::operator+=(float other)
	{
		m_X += other;
		m_Y += other;
		m_Z += other;
		return (*this);
	}

	Vector3 Vector3::operator-(float other)
	{
		return Vector3{ m_X - other , m_Y - other , m_Z - other };
	}

	Vector3& Vector3::operator-=(float other)
	{
		m_X -= other;
		m_Y -= other;
		m_Z -= other;
		return (*this);
	}

	float& Vector3::operator[](unsigned int index)
	{
		if (index > 2)
		{
			throw std::out_of_range("Index should be lower or equal to 2!");
		}

		switch (index)
		{
		case(0):
			return m_X;
		case(1):
			return m_Y;
		case(2):
			return m_Z;
		}
	}

	float Vector3::operator[](const unsigned int index) const
	{
		if (index > 2)
		{
			throw std::out_of_range("Index should be lower or equal to 2!");
		}

		switch (index)
		{
		case(0):
			return m_X;
		case(1):
			return m_Y;
		case(2):
			return m_Z;
		}
	}

	std::ostream& operator<<(std::ostream& os, const Vector3& v)
	{
		os << "{" << v.GetX() << ", " << v.GetY() << ", " << v.GetZ() << "}";
		return os;
	}
}
#pragma once

#include <iostream>

namespace ForgeEngine
{
	class Vector3
	{
		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

	private:
		float m_X{};
		float m_Y{};
		float m_Z{};

		/************************************/
		/**************METHODS***************/
		/************************************/

	public:
		Vector3(float x, float y, float z);

		static float Distance(const Vector3& v1, const Vector3& v2);
		float Distance(const Vector3& other) const;
		float GetLength() const;
		const Vector3 GetNormalized() const;

		float GetX() const { return m_X; }
		float GetY() const { return m_Y; }
		float GetZ() const { return m_Z; }

		Vector3 operator/(const Vector3& other);
		Vector3& operator/=(const Vector3& other);

		Vector3 operator*(const Vector3& other);
		Vector3& operator*=(const Vector3& other);

		Vector3 operator+(const Vector3& other);
		Vector3& operator+=(const Vector3& other);

		Vector3 operator-(const Vector3& other);
		Vector3& operator-=(const Vector3& other);

		Vector3 operator/(float other);
		Vector3& operator/=(float other);

		Vector3 operator*(float other);
		Vector3& operator*=(float other);

		Vector3 operator+(float other);
		Vector3& operator+=(float other);

		Vector3 operator-(float other);
		Vector3& operator-=(float other);

		float& operator[](const unsigned int index);
		float operator[](const unsigned int index) const;

		friend std::ostream& operator<<(std::ostream& os, const Vector3& v);
	};
}
#pragma once

#include "engine/math/Math.h"

namespace ForgeEngine
{
	class Transform
	{
		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		private:
			Matrix4 m_Matrix;

			Vector3 m_Position{0.f};
			Vector3 m_Rotation{0.f};
			Vector3 m_Scale{1.f};

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			Transform();

			const Matrix4& GetMatrix() const { return m_Matrix; }

			Vector3 GetPosition() const { return m_Position; }
			Vector3 GetRotation() const { return m_Rotation; }
			Vector3 GetScale() const { return m_Scale; }

			void SetPosition(const Vector3& position);
			void SetRotation(const Vector3& rotation);
			void SetScale(const Vector3& scale);

			void Translate(const Vector3& vector);
			void Rotate(float angle, const Vector3& axis);
			void Rotate(const Vector3& euleurAngles);
			void Scale(const Vector3& scale);

			void Refresh();
			void Reset();
	};
}
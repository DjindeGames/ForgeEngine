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

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			Transform();

			const Matrix4& GetMatrix() const { return m_Matrix; }

			inline Vector3 GetPosition() const;
			inline Vector3 GetRotation() const;
			inline Vector3 GetScale() const;

			void SetPosition(const Vector3& position);
			void SetRotation(const Vector3& rotation);
			void SetScale(const Vector3& scale);

			void Translate(const Vector3& vector);
			void Rotate(float angle, const Vector3& axis);
			void Rotate(const Vector3& euleurAngles);
			void Scale(const Vector3& scale);
	};
}
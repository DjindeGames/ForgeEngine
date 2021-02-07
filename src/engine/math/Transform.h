#pragma once

#include "engine/math/Matrix4.h"
#include "engine/math/Vector4.h"

namespace ForgeEngine
{
	class Transform
	{
		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		private:
			Matrix4 m_Matrix;

			Vector4 m_Position{0.f};
			Vector4 m_Rotation{0.f};
			Vector4 m_Scale{1.f};

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			Transform();

			const Matrix4& GetMatrix() const { return m_Matrix; }

			Vector4 GetPosition() const { return m_Position; }
			Vector4 GetRotation() const { return m_Rotation; }
			Vector4 GetScale() const { return m_Scale; }

			void SetPosition(const Vector4& position);
			void SetRotation(const Vector4& rotation);
			void SetScale(const Vector4& scale);

			void Translate(const Vector4& vector);
			void Rotate(float angle, const Vector4& axis);
			void Rotate(const Vector4& euleurAngles);
			void Scale(const Vector4& scale);

			void Refresh();
			void Reset();
	};
}
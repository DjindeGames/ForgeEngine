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

			void Translate(const Vector3& vector);
			void Rotate(float angle, const Vector3& axis);
	};
}
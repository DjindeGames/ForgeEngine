#pragma once

#include "engine/core/Component.h"

namespace ForgeEngine
{
	class ViewerComponent : public Component
	{
		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		private:
			float m_RotationSpeed;
			Transform m_InitialTransform;

		/************************************/
		/**************METHODS***************/
		/************************************/
		public:
			ViewerComponent(float rotationSpeed);

			virtual void OnInit() override;
			virtual void OnUpdate(float dT) override;

			float GetRotationSpeed() const { return m_RotationSpeed; }
			void SetRotationSpeed(float rotationSpeed) { m_RotationSpeed = rotationSpeed; }

		private:
			void ResetRotation();
	};
}
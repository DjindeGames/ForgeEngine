#pragma once

#include "engine/core/Component.h"
#include "engine/math/Transform.h"

namespace ForgeEngine
{
	class ViewerComponent : public Component
	{
		using Mother = Component;

		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		private:
			float m_TranslationSpeed;
			float m_RotationSpeed;
			float m_ScaleSpeed;
			
			Transform m_InitialTransform;

		/************************************/
		/**************METHODS***************/
		/************************************/
		public:
			ViewerComponent(float translationSpeed, float rotationSpeed, float scaleSpeed);

			virtual bool OnInit() override;
			virtual void OnUpdate(float dT) override;

			float GetRotationSpeed() const { return m_RotationSpeed; }
			void SetRotationSpeed(float rotationSpeed) { m_RotationSpeed = rotationSpeed; }

		private:
			void ResetTransform();
	};
}
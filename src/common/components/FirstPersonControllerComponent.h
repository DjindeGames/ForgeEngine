#pragma once

#include "engine/core/Component.h"

namespace ForgeEngine
{
	class FirstPersonControllerComponent : public Component
	{
		using Mother = Component;

		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		private:
			float m_MoveSpeed{};
			float m_RotationSpeed{};

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			FirstPersonControllerComponent(float moveSpeed = 5.f, float rotationSpeed = 30.f);

			virtual void OnUpdate(float dT) override;
	};
}
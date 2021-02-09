#pragma once

#include "engine/core/Component.h"

namespace ForgeEngine
{
	class InputManager;

	class FirstPersonControllerComponent : public Component
	{
		using Mother = Component;

		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		private:
			float m_MoveSpeed{};
			float m_RotationSpeed{};

			InputManager* m_InputManager{};

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			FirstPersonControllerComponent(float moveSpeed = 5.f, float rotationSpeed = 30.f);

			virtual void OnInit() override;
			virtual void OnUpdate(float dT) override;
	};
}
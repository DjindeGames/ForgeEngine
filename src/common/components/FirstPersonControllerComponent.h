#pragma once

#include "engine/core/Component.h"

namespace ForgeEngine
{
	class CameraComponent;
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
			CameraComponent* m_CameraComponent{};

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			FirstPersonControllerComponent(float moveSpeed = 10.f, float rotationSpeed = 10.f);

			virtual bool OnInit() override;
			virtual void OnUpdate(float dT) override;
	};
}
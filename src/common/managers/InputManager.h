#pragma once

#include "common/input/InputAction.h"
#include "engine/core/Defines.h"
#include "engine/core/Manager.h"
#include "system/math/Vector2.h"

#include <unordered_map>

namespace ForgeEngine
{
	class InputManager : public Manager
	{
		using Mother = Manager;

		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		private:
			std::unordered_map<EInputAction, std::unique_ptr<InputAction>> m_InputActionMappings{};
			Vector2 m_MousePosition{};
			Vector2 m_PreviousMousePosition{};

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			InputManager();

			virtual void OnPreUpdate(float dT) override;

			bool IsInputActive(EInputAction actionType) const;
			Vector2 GetMousePosition() const { return m_MousePosition; };
			Vector2 GetMouseVelocity() const { return (m_PreviousMousePosition - m_MousePosition); };

		private:
			void UpdateMousePosition();
	};
}
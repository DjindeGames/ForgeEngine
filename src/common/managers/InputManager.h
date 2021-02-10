#pragma once

#include "engine/core/Defines.h"
#include "engine/core/Manager.h"
#include "engine/math/Vector2.h"

#include <unordered_map>

namespace ForgeEngine
{
	enum class EInputAction
	{
		MoveForward,
		MoveBackward,
		MoveRight,
		MoveLeft,
		FlyUp,
		FlyDown,
		Count
	};

	class InputManager : public Manager
	{
		using Mother = Manager;

		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		private:
			std::unordered_map<EInputAction, GL_ID> m_InputActionMappings{};
			Vector2 m_MousePosition{};
			Vector2 m_PreviousMousePosition{};

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			InputManager();

			virtual void OnPreUpdate() override;

			bool IsInputActive(EInputAction actionType) const;
			Vector2 GetMousePosition() const { return m_MousePosition; };
			Vector2 GetMouseVelocity() const { return (m_PreviousMousePosition - m_MousePosition); };

		private:
			void UpdateMousePosition();
	};
}
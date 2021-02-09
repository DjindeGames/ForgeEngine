#pragma once

#include "engine/core/Defines.h"
#include "engine/core/Manager.h"

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

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			InputManager();

			bool IsInputActive(EInputAction actionType);
	};
}
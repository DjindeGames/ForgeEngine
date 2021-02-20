#pragma once

#include "system/time/Timer.h"
#include "engine/core/Object.h"

namespace ForgeEngine
{
	enum class EInputAction
	{
		ToggleWireframe,

		MoveForward,
		MoveBackward,
		MoveRight,
		MoveLeft,
		FlyUp,
		FlyDown,
		Exit,
		Count
	};

	enum class EInputType
	{
		Hold,
		Press,
		Release,
		Count
	};

	class Timer;

	class InputAction : public Object
	{
		using Mother = Object;
		using KeyID = unsigned int;

		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		private:
			static const constexpr float K_INPUT_THRESHOLD_MS = 0.1f;

			EInputType m_InputType;
			KeyID m_Key;
			bool m_IsActive{ false };

			bool m_NeedsReset{ false };

			Timer m_Timer;

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			InputAction(EInputType type, KeyID id);

			virtual void Update(float dT);
			bool IsActive() const { return m_IsActive; }

		private:
			bool IsKeyPressed() const;
	};
}
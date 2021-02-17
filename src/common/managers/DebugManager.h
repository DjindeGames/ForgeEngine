#pragma once

#include "engine/core/Manager.h"

namespace ForgeEngine
{
	class InputManager;

	class DebugManager : public Manager
	{
		using Mother = Manager;

		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		private:
			int m_CurrentDrawMode;
			InputManager* m_InputManager{};

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			DebugManager();

			virtual bool OnInit() override;
			virtual void OnUpdate(float dT) override;

		private:
			void InitImgui();
			int ComputeFramerate(float dT);
			void ProcessDebugInput();
			void ToggleWireframeMode();
	};
}
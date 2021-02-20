#pragma once

#include "engine/core/Manager.h"

namespace ForgeEngine
{
	class DebugManager : public Manager
	{
		using Mother = Manager;

		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		private:
			int m_CurrentDrawMode;

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			DebugManager();

			virtual bool OnInit() override;
			virtual void OnPostUpdate(float dT) override;

		private:
			void InitImgui();
			int ComputeFramerate(float dT);
			void ProcessDebugInput();
			void ToggleWireframeMode();
	};
}
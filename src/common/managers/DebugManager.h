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

			virtual void OnDrawDebug(float dT) override;

		private:
			int ComputeFramerate(float dT);
			void ProcessDebugInput();
			void ToggleWireframeMode();
	};
}
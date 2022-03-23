#pragma once

#include "engine/core/WorldComponent.h"

namespace ForgeEngine
{
	class DebugManager : public WorldComponent
	{
		using Mother = WorldComponent;

		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		private:
            static const unsigned int K_NB_FRAMERATE_SAMPLES{ 10 };
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
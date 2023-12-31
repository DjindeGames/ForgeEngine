#pragma once

#include "engine/core/WorldComponent.h"

namespace ForgeEngine
{
	class DebugManager : public WorldComponent
	{
		using Mother = WorldComponent;

        public:
			DebugManager();

			void OnDrawDebug(float dT) override;
            bool IsFreeMouseEnabled() const { return m_FreeMouseEnabled; }

		private:
			int ComputeFramerate(float dT);
			void ProcessDebugInput();
			void ToggleWireframeMode();
			void ToggleFreeMouse();

            static const unsigned int K_NB_FRAMERATE_SAMPLES{ 10 };
            int m_CurrentDrawMode;
            int m_FreeMouseEnabled{ false };
	};
}
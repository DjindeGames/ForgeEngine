#pragma once

#include "engine/core/WorldComponent.h"

namespace ForgeEngine
{
	class DebugManager : public WorldComponent
	{
		using Mother = WorldComponent;

        public:
			DebugManager();

            void OnUpdate(float dT) override;

#ifdef FORGE_DEBUG_ENABLED
			void OnDrawDebug(float dT) const override;
            const char* GetDebugName() const override { return "DebugManager"; }
#endif //FORGE_DEBUG_ENABLED

            bool IsFreeMouseEnabled() const { return m_FreeMouseEnabled; }

		private:
			void ComputeFramerate(float dT);
			void ProcessDebugInput();
			void ToggleWireframeMode();
			void ToggleFreeMouse();

            static const unsigned int K_NB_FRAMERATE_SAMPLES{ 10 };
            int m_CurrentDrawMode;
            int m_FreeMouseEnabled{ false };
            int m_FrameRate;
	};
}
#pragma once

#include "engine/core/WorldComponent.h"

#include "engine/core/Defines.h"
#include "system/math/Vector3.h"

#include <vector>

namespace ForgeEngine
{
    class LightComponent;

    class LightManager : public WorldComponent
    {
        using Mother = WorldComponent;

        public:
            LightManager();

            void RegisterLight(const LightComponent* light);
            void RemoveLight(const LightComponent* light);

            std::vector<const LightComponent*> GetLightsInRange(const Vector3& position);

        private:
            std::vector<const LightComponent*> m_RegisteredLights{};
    };
}
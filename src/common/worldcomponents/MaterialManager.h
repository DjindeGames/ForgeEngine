#pragma once

#include "engine/core/WorldComponent.h"

#include "engine/shader/Material.h"

#include <vector>

namespace ForgeEngine
{
    class MaterialManager : public WorldComponent
    {
        using Mother = WorldComponent;

        public:
            Material* LoadMaterial(const char* materialPath);
            Material* GetMaterial(const char* materialPath);
            
            void OnDrawDebug(float dT) override;

        private:
            static bool IsMaterialLoaded(const char* materialPath);

            using MaterialData = std::pair<const char*, Material>;
            std::vector<MaterialData> m_LoadedMaterials;
    };
}

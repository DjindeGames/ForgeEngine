#pragma once

#include "engine/core/Defines.h"
#include "engine/core/WorldComponent.h"

#include "engine/shader/Material.h"

#include <vector>

namespace ForgeEngine
{
    class Color;

    class MaterialManager : public WorldComponent
    {
        using Mother = WorldComponent;

        public:
            MaterialManager();

            Material* GetDefaultMaterial() { return GetMaterial("DEFAULT"); }
            Material* LoadMaterial(const char* materialPath);
            Material* LoadMaterial(const Color& color);
            Material* GetMaterial(const char* materialPath);
            
            void OnDrawDebug(float dT) override;

        private:
            static bool IsMaterialLoaded(const char* materialPath);

            using MaterialData = std::pair<const char*, Unique<Material>>;
            std::vector<MaterialData> m_LoadedMaterials;
    };
}

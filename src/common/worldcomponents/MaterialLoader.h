#pragma once

#include "engine/core/ResourceLoader.h"

namespace ForgeEngine
{
    class Material;

    class MaterialLoader : public ResourceLoader<Material>
    {
        using Mother = ResourceLoader<Material>;

        protected:
            bool AddResource(const std::string& resourcePath) override;
            const char* GetName() { return "Loaded Materials"; }
    };
}

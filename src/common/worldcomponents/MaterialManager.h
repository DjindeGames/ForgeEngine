#pragma once

#include "engine/core/ResourceLoader.h"

namespace ForgeEngine
{
    class Material;

    class MaterialManager : public ResourceLoader<Material>
    {
        using Mother = ResourceLoader<Material>;

        protected:
            void AddResource(const std::string& resourcePath, const std::string& resourceContent) override;
            const char* GetName() { return "MaterialLoader"; }
    };
}

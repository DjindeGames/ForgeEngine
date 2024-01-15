#pragma once

#include "engine/core/ResourceLoader.h"

namespace ForgeEngine
{
    class Texture;

    class TextureLoader : public ResourceLoader<Texture>
    {
        using Mother = ResourceLoader<Texture>;

    protected:
        void AddResource(const std::string& resourcePath, const std::string& resourceContent) override;
        const char* GetName() { return "Loaded Textures"; }
    };
}

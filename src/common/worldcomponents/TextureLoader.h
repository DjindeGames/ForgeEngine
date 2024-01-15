#pragma once

#include "engine/core/ResourceLoader.h"

namespace ForgeEngine
{
    class Texture;

    class TextureLoader : public ResourceLoader<Texture>
    {
        using Mother = ResourceLoader<Texture>;

    protected:
        bool AddResource(const std::string& resourcePath) override;
        const char* GetName() { return "Loaded Textures"; }
    };
}

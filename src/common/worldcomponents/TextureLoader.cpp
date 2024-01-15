#include "TextureLoader.h"

#include "engine/misc/Texture.h"

namespace ForgeEngine
{
    void TextureLoader::AddResource(const std::string& resourcePath, const std::string& resourceContent)
    {
        m_LoadedResources[resourcePath] = std::shared_ptr<Texture>(new Texture(resourcePath.c_str()));
    }
}
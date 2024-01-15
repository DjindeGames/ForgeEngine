#include "MaterialLoader.h"

#include "engine/shader/Material.h"

namespace ForgeEngine
{
    void MaterialLoader::AddResource(const std::string& resourcePath, const std::string& resourceContent)
    {
        m_LoadedResources[resourcePath] = std::shared_ptr<Material>(new Material(resourceContent));
    }
}
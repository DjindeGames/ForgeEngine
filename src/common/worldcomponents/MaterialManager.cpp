#include "MaterialManager.h"

#include "engine/shader/Material.h"

namespace ForgeEngine
{
    void MaterialManager::AddResource(const std::string& resourcePath, const std::string& resourceContent)
    {
        m_LoadedResources[resourcePath] = std::shared_ptr<Material>(new Material(resourceContent));
    }
}
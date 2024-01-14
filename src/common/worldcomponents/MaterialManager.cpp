#include "MaterialManager.h"

#include "engine/shader/Material.h"

namespace ForgeEngine
{
    void MaterialManager::AddResource(const std::string& resourcePath, const std::string& resourceContent)
    {
        m_LoadedResources[resourcePath.c_str()] = std::shared_ptr<Material>(new Material(resourceContent));
    }
}
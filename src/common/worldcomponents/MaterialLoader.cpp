#include "MaterialLoader.h"

#include "engine/shader/Material.h"
#include "system/io/FileUtils.h"

namespace ForgeEngine
{
    bool MaterialLoader::AddResource(const std::string& resourcePath)
    {
        std::string resourceContent;
        bool success = FileUtils::TryLoadFileContent(resourcePath, resourceContent);

        if (success)
        {
            m_LoadedResources[resourcePath] = std::shared_ptr<Material>(new Material(resourceContent));
        }

        return success;
    }
}
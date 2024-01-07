#include "MaterialManager.h"

#ifdef FORGE_DEBUG_ENABLED
#include "engine/ui/ImGUI.h"
#endif //FORGE_DEBUG_ENABLED

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace ForgeEngine
{
#ifdef FORGE_DEBUG_ENABLED
    void MaterialManager::OnDrawDebug(float dT) /*override*/
    {
        Mother::OnDrawDebug(dT);

        ImGui::Begin("MaterialManager");
        for (MaterialData& data : m_LoadedMaterials)
        {
            if (ImGui::CollapsingHeader(data.first))
            {
                data.second.OnDrawDebug();
            }
            
        }
        ImGui::End();
    }
#endif //FORGE_DEBUG_ENABLED

    Material* MaterialManager::LoadMaterial(const char* materialPath)
    {
        Material* material = GetMaterial(materialPath);

        if (material == nullptr)
        {
            //TODO: make this a util function
            std::ifstream sourceFile;
            std::stringstream sourceStream;
            std::string sourceContent{};

            // ensure ifstream objects can throw exceptions:
            sourceFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

            try
            {
                sourceFile.open(materialPath);
                sourceStream << sourceFile.rdbuf();
                sourceFile.close();

                sourceContent = sourceStream.str();

                m_LoadedMaterials.push_back(MaterialData(materialPath, Material(sourceContent)));
                material = &m_LoadedMaterials.back().second;
            }
            catch (std::ifstream::failure failure)
            {
                std::cout << "MaterialAtlas: Cannot open source path " << materialPath << "." << std::endl;
            }
        }
        
        return material;
    }

    Material* MaterialManager::GetMaterial(const char* materialPath)
    {
        for (MaterialData& data : m_LoadedMaterials)
        {
            if (materialPath == data.first)
            {
                return &data.second;
            }
        }
        return nullptr;
    }
}
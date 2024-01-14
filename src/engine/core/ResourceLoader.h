#pragma once

#include "engine/core/WorldComponent.h"
#include "system/io/FileUtils.h"

#ifdef FORGE_DEBUG_ENABLED
#include "engine/ui/ImGUI.h"
#endif //FORGE_DEBUG_ENABLED

#include <memory>
#include <string>
#include <unordered_map>

namespace ForgeEngine
{
    template <typename T>
    class ResourceLoader : public WorldComponent
    {
        using Mother = WorldComponent;
#define DEFAULT_RESOURCE_NAME "_default"

    public:
        const std::shared_ptr<T>* GetOrLoadResource(const std::string& resourcePath)
        {
            const std::shared_ptr<T>* resource = GetResource(resourcePath);

            if (!IsResourceLoaded(resourcePath))
            {
                if (resourcePath != DEFAULT_RESOURCE_NAME)
                {
                    std::string resourceContent;
                    if (TryLoadResourceContent(resourcePath, resourceContent))
                    {
                        AddResource(resourcePath, resourceContent);
                    }
                    else
                    {
                        return GetDefault();
                    }
                }
                else
                {
                    AddResource(resourcePath, "");
                }
            }

            return GetResource(resourcePath);
        }

        const std::shared_ptr<T>* GetDefault()
        {
            return GetOrLoadResource(DEFAULT_RESOURCE_NAME);
        }

        void OnPostUpdate(float dT) override
        {
            Mother::OnPostUpdate(dT);

            for (auto it = m_LoadedResources.begin(); it != m_LoadedResources.end();) 
            {
                if ((*it).second.unique())
                {
                    it = m_LoadedResources.erase(it);
                }
                else
                {
                    it++;
                }
            }
        }

#ifdef FORGE_DEBUG_ENABLED
        void OnDrawDebug(float dT) override
        {
            Mother::OnDrawDebug(dT);

            ImGui::Begin(GetName());
            for (const Resource& resource : m_LoadedResources)
            {
                if (ImGui::CollapsingHeader(resource.first.c_str()))
                {
                    //resource.second.get()->OnDrawDebug();
                }
            }
            ImGui::End();
        }
#endif //FORGE_DEBUG_ENABLED

        protected:
            virtual void AddResource(const std::string& resourcePath, const std::string& resourceContent) = 0;
            virtual const char* GetName() = 0;

            bool IsResourceLoaded(const std::string& resourcePath)
            {
                auto it = m_LoadedResources.find(resourcePath);
                return (it != m_LoadedResources.end()) ? true : false;
            }

            const std::shared_ptr<T>* GetResource(const std::string& resourcePath)
            {
                auto it = m_LoadedResources.find(resourcePath);
                return (it != m_LoadedResources.end()) ? &((*it).second) : nullptr;
            }

            bool TryLoadResourceContent(const std::string& resourcePath, std::string& resourceContent)
            {
                return FileUtils::TryLoadFileContent(resourcePath, resourceContent);
            }

            using Resource = std::pair<const std::string&, const std::shared_ptr<T>&>;
            std::unordered_map<std::string, std::shared_ptr<T>> m_LoadedResources{};
    };
}
#include "Material.h"

#include "engine/misc/Texture.h"

#ifdef FORGE_DEBUG_ENABLED
#include "engine/ui/ImGUI.h"
#endif //FORGE_DEBUG_ENABLED

#include "system/misc/Utils.h"

#include <vector>

namespace ForgeEngine
{
    Material::Material(const std::string& source)
    {
        std::vector<std::string> attributes = ForgeUtils::Split("\n", source);

        if (!source.empty())
        {
            for (const std::string& attribute : attributes)
            {
                std::vector<std::string> splittedAttribute = ForgeUtils::Split(":", attribute);
                const std::string& name = splittedAttribute[0];

                if (splittedAttribute.size() == 2)
                {
                    if (!ResolveAttribute(name, splittedAttribute[1]))
                    {
                        std::cout << "Material: Cannot resolve attribute " << name << "." << std::endl;
                    }
                }
                else
                {
                    std::cout << "Material: Invalid syntax on line " << name << "." << std::endl;
                }
            }
        }
        else
        {
            m_Color = COLOR_MAGENTA;
        }
    }

    Material::~Material()
    {
        if (m_Texture != nullptr)
        {
            delete(m_Texture);
        }
    }

    bool Material::ResolveAttribute(const std::string& name, const std::string& value)
    {
        bool success = true;

        if (name == "color")
        {
            std::vector<std::string> components = ForgeUtils::Split(";", value);
            if (components.size() == 4)
            {
                m_Color = Color(stoi(components[0]), stoi(components[1]), stoi(components[2]), stof(components[3]));
            }
            else
            {
                success = false;
            }
        }
        else if (name == "diffuse")
        {
            m_Diffuse = stof(value);
        }
        else if (name == "specular")
        {
            m_Specular = stof(value);
        }
        else if (name == "shininess")
        {
            m_Shininess = stoi(value);
        }
        else if (name == "texture")
        {
            //TODO: Reuse texture if already exists
            m_Texture = new Texture(value.c_str());
        }
        else
        {
            success = false;
        }

        return success;
    }

#ifdef FORGE_DEBUG_ENABLED
    void Material::OnDrawDebug() const
    {
        ImGui::Text("Diffuse: %.2f", m_Diffuse);
        ImGui::Text("Specular: %.2f", m_Specular);
        ImGui::Text("Shininess: %d", m_Shininess);
        float color[4]{ m_Color.GetR(), m_Color.GetG(), m_Color.GetB(), m_Color.GetA() };
        ImGui::ColorEdit4("Color: %s", color);
        if (m_Texture != nullptr)
        {
            ImGui::Text("Texture: %s", m_Texture->GetName());
        }
    }
#endif //FORGE_DEBUG_ENABLED
}

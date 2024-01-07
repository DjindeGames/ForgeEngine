#pragma once

#include "system/misc/Color.h"

#include <string>

namespace ForgeEngine
{
    class MaterialManager;

    class Material
    {
        friend class MaterialManager;

        private:
            Material(const std::string& source);
#ifdef FORGE_DEBUG_ENABLED
            void OnDrawDebug() const;
#endif //FORGE_DEBUG_ENABLED

            bool ResolveAttribute(const std::string& name, const std::string& value);

            int m_Shininess;
            float m_Specular;
            Color m_Color;
    };
}
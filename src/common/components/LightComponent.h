#pragma once

#include "engine/core/Component.h"
#include "system/misc/Color.h"

namespace ForgeEngine
{
    class LightComponent : public Component
    {
        using Mother = Component;

    public:
        LightComponent(float range = 1.f, float intensity = 1.f, const Color& color = COLOR_WHITE);

        float GetRange() const { return m_Range; }
        float GetIntensity() const { return m_Intensity; }
        const Color& GetColor() const { return m_Color; }

    protected:
        bool OnInit() override;
        void OnDestroy() override;

    private:
        float m_Range{ 1.f };
        float m_Intensity{ 1.f };
        Color m_Color{ COLOR_WHITE };
    };
}
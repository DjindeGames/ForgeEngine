#include "LightComponent.h"

#include "common/worldcomponents/LightManager.h"
#include "engine/core/GameHandler.h"

namespace ForgeEngine
{
    LightComponent::LightComponent(float range /*= 1.f*/, float intensity /*= 1.f*/, const Color& color /*= COLOR_WHITE*/)
        : Mother()
        , m_Range(range)
        , m_Intensity(intensity)
        , m_Color(color)
    {
    }

    void LightComponent::OnDestroy()
    {
        GameHandler::Get().GetWorld().GetComponentByType<LightManager>()->RemoveLight(this);
        Mother::OnDestroy();
    }

    bool LightComponent::OnInit() /*override*/
    { 
        Mother::OnInit();

        GameHandler::Get().GetWorld().GetComponentByType<LightManager>()->RegisterLight(this);

        return true; 
    }
}

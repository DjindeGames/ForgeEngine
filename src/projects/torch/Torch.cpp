#include "Torch.h"

#include "common/components/FirstPersonControllerComponent.h"
#include "common/components/CameraComponent.h"
#include "common/components/LightComponent.h"
#include "common/components/MeshComponent.h"
#include "common/helpers/InputHelper.h"
#include "common/helpers/MeshUtils.h"
#include "common/worldcomponents/DebugManager.h"
#include "common/worldcomponents/InputManager.h"
#include "common/worldcomponents/MaterialManager.h"
#include "common/worldcomponents/ShaderManager.h"
#include "engine/core/ForgeEngine.h"
#include "engine/misc/Texture.h"
#include "engine/shader/ShaderUtils.h"

#include "system/misc/Color.h"

int main()
{
    Torch::Torch instance("Torch", 1280, 720);
    instance.HandleProcess();
}

namespace Torch
{
    Torch::Torch(std::string name, unsigned int width, unsigned int height) :
        Mother(name, width, height)
    {
    }

    void Torch::OnInit() /*override*/
    {
        Mother::OnInit();

        World& world = GetWorld();

        Entity* ground = world.RegisterEntity();
        ground->RegisterComponent(new MeshComponent(MeshUtils::MakePlane(100.f, COLOR_WHITE, new Texture("assets\\daggerfall\\textures\\grounds\\grass.PNG")), world.GetComponentByType<ShaderManager>()->GetShaderByType(EShaderType::Lit)));
        
        Material* mat = world.GetComponentByType<MaterialManager>()->LoadMaterial("assets\\materials\\ruby.mat");

        Color lightColor = COLOR_WHITE;
        m_Light = world.RegisterEntity();
        m_Light->RegisterComponent(new MeshComponent(MeshUtils::MakeCube(0.1f, lightColor), world.GetComponentByType<ShaderManager>()->GetShaderByType(EShaderType::Default)));
        m_Light->RegisterComponent(new LightComponent(30.f, 10.f, lightColor));
        m_Light->GetTransform().Translate(VECTOR3_UP * 3.f + VECTOR3_SIDE * 2.f);
        
        Entity* player = world.RegisterEntity();
        player->RegisterComponent(new CameraComponent(CameraComponent::PerspectiveCamera{}));
        player->RegisterComponent(new FirstPersonControllerComponent());
        player->GetTransform().SetPosition(Vector3(-40.f, 1.7f, 42.f));
        
        Entity* cube1 = world.RegisterEntity();
        cube1->RegisterComponent(new MeshComponent(MeshUtils::MakeCube(1.f, COLOR_WHITE, new Texture("assets\\daggerfall\\textures\\grounds\\stone.PNG")), world.GetComponentByType<ShaderManager>()->GetShaderByType(EShaderType::Lit)));
        cube1->GetTransform().Translate(VECTOR3_UP * 0.5f);
        
        m_Cube = world.RegisterEntity();
        m_Cube->RegisterComponent(new MeshComponent(MeshUtils::MakeCube(1.f, COLOR_YELLOW), world.GetComponentByType<ShaderManager>()->GetShaderByType(EShaderType::Lit)));
        m_Cube->GetTransform().Translate(Vector3(4.f, 0.5f, 4.f));
    }

    void Torch::OnUpdate(float dT) /*override*/
    {
        Mother::OnUpdate(dT);
        ShaderUtils::ClearScreen(COLOR_BLACK);
        //m_Light->GetTransform().Translate(VECTOR3_SIDE * 1.f * dT);
        m_Cube->GetTransform().Rotate(VECTOR3_UP * 90.f * dT);
    }

    void Torch::OnTermination() /*override*/
    {
        Mother::OnTermination();
    }

    bool Torch::ShouldTerminate() /*override*/
    {
        return Mother::ShouldTerminate()
            || InputHelper::IsInputActive(EInputAction::Exit);
    }
}
#include "Newton.h"

#include "common/components/FirstPersonControllerComponent.h"
#include "common/components/CameraComponent.h"
#include "common/components/MeshComponent.h"
#include "common/helpers/InputHelper.h"
#include "common/helpers/MeshUtils.h"
#include "common/worldcomponents/InputManager.h"
#include "common/worldcomponents/ShaderManager.h"
#include "common/worldcomponents/DebugManager.h"
#include "engine/core/ForgeEngine.h"
#include "engine/misc/Texture.h"
#include "engine/shader/ShaderUtils.h"

#include "system/misc/Color.h"

int main()
{
    Newton::Newton instance("Newton", 1280, 720);
    instance.HandleProcess();
}

namespace Newton
{
    Newton::Newton(std::string name, unsigned int width, unsigned int height) :
        Mother(name, width, height)
    {
    }

    void Newton::OnInit() /*override*/
    {
        Mother::OnInit();

        World* world = GetWorld();

        Entity* player = world->RegisterEntity();
        player->RegisterComponent(new CameraComponent(CameraComponent::PerspectiveCamera{}));
        player->RegisterComponent(new FirstPersonControllerComponent());
        player->GetTransform()->SetPosition(Vector3(0.f, 1.8f, 0.f));

        Entity* ground = world->RegisterEntity();
        ground->RegisterComponent(new MeshComponent(MeshUtils::GetPlaneVerticesCoordinates(10.f), MeshUtils::GetPlaneVerticesIndexes(), world->GetComponentByType<ShaderManager>()->GetShaderByType(EShaderType::Default), COLOR_LIGHT_GREY));
        Entity* cube = world->RegisterEntity();
        cube->RegisterComponent(new MeshComponent(MeshUtils::GetCubeVerticesCoordinates(), MeshUtils::GetCubeVerticesIndexes(), world->GetComponentByType<ShaderManager>()->GetShaderByType(EShaderType::Default), COLOR_RED));
        cube->GetTransform()->Translate(VECTOR3_Y * 0.5f);
        cube->GetTransform()->Scale(Vector3(2.f, 1.f, 1.f));
    }

    void Newton::OnUpdate(float dT) /*override*/
    {
        Mother::OnUpdate(dT);
        ShaderUtils::ClearScreen(COLOR_SKY_BLUE);
    }

    void Newton::OnTermination() /*override*/
    {
        Mother::OnTermination();
    }

    bool Newton::ShouldTerminate() /*override*/
    {
        return Mother::ShouldTerminate()
            || InputHelper::IsInputActive(EInputAction::Exit);
    }
}
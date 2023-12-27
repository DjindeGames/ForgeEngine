#include "Torch.h"

#include "common/components/FirstPersonControllerComponent.h"
#include "common/components/CameraComponent.h"
#include "common/components/LightComponent.h"
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

        Entity* lightCube = world.RegisterEntity();
        lightCube->RegisterComponent(new MeshComponent(MeshUtils::GetCubeVerticesCoordinates(), MeshUtils::GetCubeVerticesIndexes(), world.GetComponentByType<ShaderManager>()->GetShaderByType(EShaderType::Default), COLOR_WHITE));
        lightCube->RegisterComponent(new LightComponent());
        lightCube->GetTransform().Translate(VECTOR3_UP * 3.f);
        lightCube->GetTransform().Scale(0.1f);

        Entity* player = world.RegisterEntity();
        player->RegisterComponent(new CameraComponent(CameraComponent::PerspectiveCamera{}));
        player->RegisterComponent(new FirstPersonControllerComponent());
        player->GetTransform().SetPosition(Vector3(0.f, 1.7f, 0.f));

        Entity* ground = world.RegisterEntity();
        ground->RegisterComponent(new MeshComponent(MeshUtils::GetPlaneVerticesCoordinatesTextured(30.f), MeshUtils::GetPlaneVerticesIndexes(), world.GetComponentByType<ShaderManager>()->GetShaderByType(EShaderType::Textured), new Texture("assets\\daggerfall\\textures\\grounds\\grass.PNG")));
        
        Entity* cube1 = world.RegisterEntity();
        cube1->RegisterComponent(new MeshComponent(MeshUtils::GetCubeVerticesCoordinates(), MeshUtils::GetCubeVerticesIndexes(), world.GetComponentByType<ShaderManager>()->GetShaderByType(EShaderType::Lit), COLOR_LIGHT_GREY));
        cube1->GetTransform().Translate(VECTOR3_UP * 0.5f);

        Entity* cube2 = world.RegisterEntity();
        cube2->RegisterComponent(new MeshComponent(MeshUtils::GetCubeVerticesCoordinates(), MeshUtils::GetCubeVerticesIndexes(), world.GetComponentByType<ShaderManager>()->GetShaderByType(EShaderType::Default), COLOR_YELLOW));
        cube2->GetTransform().Translate(Vector3(4.f, 0.5f, 4.f));
    }

    void Torch::OnUpdate(float dT) /*override*/
    {
        Mother::OnUpdate(dT);
        ShaderUtils::ClearScreen(COLOR_BLACK);
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
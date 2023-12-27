#include "Daggerfall.h"

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

void mained()
{
    Daggerfall::Daggerfall instance("Daggerfall", 1280, 720);
    instance.HandleProcess();
}

namespace Daggerfall
{
    Daggerfall::Daggerfall(std::string name, unsigned int width, unsigned int height) :
        Mother(name, width, height)
    {
    }

    void Daggerfall::OnInit() /*override*/
    {
        Mother::OnInit();

        World& world = GetWorld();

        Entity* player = world.RegisterEntity();
        player->RegisterComponent(new CameraComponent(CameraComponent::PerspectiveCamera{}));
        player->RegisterComponent(new FirstPersonControllerComponent());
        player->GetTransform().SetPosition(Vector3(0.f, 1.8f, 0.f));

        Entity* ground = world.RegisterEntity();

        std::vector<float> verticesTexturesCoordinates{
                // positions       // texture coords
             -0.5f, -0.5f, -0.5f,   100.f, 100.f, // top right
            -0.5f, -0.5f,  0.5f,    100.f, 0.f, // bottom right
             0.5f, -0.5f,  0.5f,    0.f, 0.f, // bottom left
             0.5f, -0.5f, -0.5f,    0.f, 100.f  // top left 
        };

        //Coordinate indexes 
        std::vector<unsigned int> coordinates = {
            0, 1, 3,
            1, 2, 3
        };

        const float planeScale = 10.f;

        ground->RegisterComponent(new MeshComponent(MeshUtils::GetPlaneVerticesCoordinatesTextured(planeScale), MeshUtils::GetPlaneVerticesIndexes(), world.GetComponentByType<ShaderManager>()->GetShaderByType(EShaderType::Textured), new Texture("assets\\daggerfall\\textures\\grounds\\grass.PNG")));
        ground->GetTransform().Scale(Vector3(planeScale, 0.f, planeScale));
    }

    void Daggerfall::OnUpdate(float dT) /*override*/
    {
        Mother::OnUpdate(dT);
        ShaderUtils::ClearScreen(COLOR_SKY_BLUE);
    }

    void Daggerfall::OnTermination() /*override*/
    {
        Mother::OnTermination();
    }

    bool Daggerfall::ShouldTerminate() /*override*/
    {
        return Mother::ShouldTerminate()
            || InputHelper::IsInputActive(EInputAction::Exit);
    }
}
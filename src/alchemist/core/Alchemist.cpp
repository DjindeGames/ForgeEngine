#include "Alchemist.h"

#include "alchemist/core/LandscapeComponent.h"
#include "common/components/FirstPersonControllerComponent.h"
#include "common/components/CameraComponent.h"
#include "common/helpers/InputHelper.h"
#include "common/managers/InputManager.h"
#include "common/managers/ShaderManager.h"
#include "common/managers/DebugManager.h"
#include "engine/core/Entity.h"
#include "engine/core/ManagerContainer.h"
#include "engine/misc/Texture.h"
#include "engine/shader/ShaderUtils.h"
#include "system/misc/Color.h"

int main()
{
	Alchemist::Alchemist instance{};
	instance.Init("Alchemist", ALCHEMIST_WINDOW_WIDTH, ALCHEMIST_WINDOW_HEIGHT);
	instance.HandleProcess();
}

namespace Alchemist
{
	void Alchemist::OnInit() /*override*/
	{
		Mother::OnInit();

		ManagerContainer::Get()->RegisterManager(new ShaderManager());
		ManagerContainer::Get()->RegisterManager(new InputManager());
		ManagerContainer::Get()->RegisterManager(new DebugManager());

		Entity* landscape = EntityContainer::Get()->RegisterEntity();
		landscape->RegisterComponent(new LandscapeComponent());

		Entity* camera = EntityContainer::Get()->RegisterEntity();
		camera->RegisterComponent(new CameraComponent(CameraComponent::OrthographicCamera{ ALCHEMIST_WINDOW_WIDTH, ALCHEMIST_WINDOW_HEIGHT, 0.f, 100.f}));
		camera->SetPosition(Vector3(0.f, 0.f, 1.f));
	}

	void Alchemist::OnUpdate(float dT) /*override*/
	{
		Mother::OnUpdate(dT);
		ShaderUtils::ClearScreen(COLOR_WHITE);
	}

	void Alchemist::OnTermination() /*override*/
	{
		Mother::OnTermination();
	}

	bool Alchemist::ShouldTerminate() /*override*/
	{
		return Mother::ShouldTerminate()
			|| InputHelper::IsInputActive(EInputAction::Exit);
	}
}
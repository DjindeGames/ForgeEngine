#include "PapierKraft.h"

#include "common/components/CameraComponent.h"
#include "common/components/FirstPersonControllerComponent.h"
#include "common/helpers/InputHelper.h"
#include "common/managers/InputManager.h"
#include "common/managers/ShaderManager.h"
#include "common/managers/DebugManager.h"
#include "engine/core/Entity.h"
#include "engine/core/ManagerContainer.h"
#include "engine/shader/ShaderUtils.h"
#include "papierkraft/components/BlockComponent.h"
#include "papierkraft/components/ChunkComponent.h"
#include "papierkraft/managers/BlockTextureManager.h"
#include "system/misc/Color.h"

void mained()
{
	PapierKraft::PapierKraft instance{};
	instance.Init("PapierKraft", 1280, 720);
	instance.HandleProcess();
}

namespace PapierKraft
{
	void PapierKraft::OnInit() /*override*/
	{
		Mother::OnInit();

		ManagerContainer::Get()->RegisterManager(new BlockTextureManager());
		ManagerContainer::Get()->RegisterManager(new ShaderManager());
		ManagerContainer::Get()->RegisterManager(new InputManager());
		ManagerContainer::Get()->RegisterManager(new DebugManager());

		Entity* block = EntityContainer::Get()->RegisterEntity();
		block->RegisterComponent(new BlockComponent(EBlockType::Grass));

		Entity* camera = EntityContainer::Get()->RegisterEntity();
		camera->RegisterComponent(new FirstPersonControllerComponent());
		camera->RegisterComponent(new CameraComponent(CameraComponent::PerspectiveCamera{}));
	}

	void PapierKraft::OnUpdate(float dT) /*override*/
	{
		Mother::OnUpdate(dT);
		ShaderUtils::ClearScreen(COLOR_SKY_BLUE);
	}

	void PapierKraft::OnTermination() /*override*/
	{
		Mother::OnTermination();
	}

	bool PapierKraft::ShouldTerminate() /*override*/
	{
		return Mother::ShouldTerminate()
			|| InputHelper::IsInputActive(EInputAction::Exit);
	}
}
#include "PapierKraft.h"

#include "common/components/CameraComponent.h"
#include "common/components/FirstPersonControllerComponent.h"
#include "common/components/MeshComponent.h"
#include "common/managers/InputManager.h"
#include "common/managers/ShaderManager.h"

#include "engine/core/Entity.h"
#include "engine/core/Game.h"
#include "engine/core/ManagerContainer.h"
#include "system/misc/Color.h"
#include "engine/shader/ShaderUtils.h"

#include "papierkraft/test/BlockComponent.h"
#include "papierkraft/test/BlockTextureManager.h"
#include "papierkraft/test/Chunk.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace ForgeEngine;

int main()
{
	return PapierKraft::CoreLoop();
}

namespace PapierKraft
{
	//Try anything here
	void PerformTests()
	{

	}

	int CoreLoop()
	{
		Game game;
		game.Init("PapierKraft", 1280, 720);
		game.SetUpdateCallback(Update);
		game.SetTerminationConditionCallback(ShouldTerminate);

		PerformTests();

		Init();

		game.HandleProcess();
		
		ReleaseResources();

		return 0;
	}

	void ReleaseResources()
	{
	}

	void Update(float dT)
	{
		ProcessInput();
		ShaderUtils::ClearScreen(COLOR_SKY_BLUE);
	}

	void ProcessInput()
	{
	}

	bool ShouldTerminate()
	{
		return (
			glfwGetKey(Game::m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS ||
			glfwGetKey(Game::m_Window, GLFW_KEY_ENTER) == GLFW_PRESS
			);
	}

	void Init()
	{
		ManagerContainer::Get()->RegisterManager(new BlockTextureManager());
		ManagerContainer::Get()->RegisterManager(new ShaderManager());
		ManagerContainer::Get()->RegisterManager(new InputManager());

		Chunk chunk(EBiomeType::Plain, VECTOR3_NULL);

		Entity* camera = EntityContainer::Get()->RegisterEntity();
		camera->SetPosition(Vector3{ 0.f, 8.f, 0.f });
		camera->RegisterComponent(new FirstPersonControllerComponent());
		camera->RegisterComponent(new CameraComponent());
	}
}
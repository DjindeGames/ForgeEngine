#include "PapierKraft.h"

#include "common/components/CameraComponent.h"
#include "common/components/FirstPersonControllerComponent.h"
#include "common/components/MeshComponent.h"
#include "common/managers/InputManager.h"
#include "common/managers/ShaderManager.h"

#include "engine/core/Entity.h"
#include "engine/core/Game.h"
#include "engine/core/ManagerContainer.h"
#include "engine/misc/Color.h"
#include "engine/shader/ShaderUtils.h"

#include "BlockComponent.h"
#include "BlockTextureManager.h"

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
		game.Init("PapierKraft", 800, 450);
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

		BuildChunk();

		Entity* camera = EntityContainer::Get()->RegisterEntity();
		camera->RegisterComponent(new CameraComponent(45.f));
		camera->RegisterComponent(new FirstPersonControllerComponent());
		camera->SetPosition(Vector4{ 0.f, 0.f, 10.f, 0.f });
	}

	void BuildChunk()
	{
		for (float x = -1.f; x < 2.f; x++)
		{
			for (float z = -1.f; z < 2.f; z++)
			{
				Entity* block = EntityContainer::Get()->RegisterEntity();
				block->RegisterComponent(new BlockComponent(EBlockType::Grass));
				block->SetPosition(Vector4{ x, 0.f, z, 0.f });
			}
		}
		for (float x = -1.f; x < 2.f; x++)
		{
			for (float z = -1.f; z < 2.f; z++)
			{
				for (float y = -1.f; y > -3.f; y--)
				{
					Entity* block = EntityContainer::Get()->RegisterEntity();
					block->RegisterComponent(new BlockComponent(EBlockType::Stone));
					block->SetPosition(Vector4{ x, y, z, 0.f });
				}
			}
		}

		Entity* block = EntityContainer::Get()->RegisterEntity();
		block->RegisterComponent(new BlockComponent(EBlockType::Woodlog));
		block->SetPosition(Vector4{ 0.f, 1.f, 0.f, 0.f });
	}
}
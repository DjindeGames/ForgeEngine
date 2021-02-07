#include "PapierKraft.h"

#include "common/components/MeshComponent.h"
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
		game.Init("PapierKraft", 800, 600);
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

		Entity* entity = EntityContainer::Get()->RegisterEntity();
		entity->RegisterComponent(new BlockComponent(EBlockType::Woodlog));
	}
}
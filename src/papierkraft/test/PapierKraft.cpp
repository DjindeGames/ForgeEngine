#include "PapierKraft.h"

#include "engine/3d/MeshComponent.h"
#include "engine/core/Entity.h"
#include "engine/core/Game.h"
#include "engine/misc/Color.h"
#include "engine/misc/Texture.h"
#include "engine/shader/Shader.h"
#include "engine/shader/ShaderUtils.h"

#include "BlockComponent.h"
#include "BlockTexturesManager.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

using namespace ForgeEngine;

Shader* defaultShader;

Texture* grassTextureSide;
Texture* grassTextureTop;
Texture* grassTextureBottom;
Texture* dirtTextureUniform;
Texture* stoneTextureUniform;
Texture* logTextureSide;
Texture* logTextureRest;

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

		BuildBlocks();

		game.HandleProcess();
		
		ReleaseResources();

		return 0;
	}

	void ReleaseResources()
	{
		delete(defaultShader);
		delete(grassTextureSide);
		delete(grassTextureTop);
		delete(grassTextureBottom);
		delete(dirtTextureUniform);
		delete(stoneTextureUniform);
		delete(logTextureRest);
		delete(logTextureSide);
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

	void BuildBlocks()
	{
		defaultShader = new Shader{ TEXTURED_VERTEX_SHADER_PATH, TEXTURED_FRAGMENT_SHADER_PATH };

		grassTextureSide = new Texture{ TEXTURE_GRASS_SIDE, GL_RGBA };
		grassTextureTop = new Texture{ TEXTURE_GRASS_TOP, GL_RGBA };
		grassTextureBottom = new Texture{ TEXTURE_GRASS_BOTTOM, GL_RGBA };

		dirtTextureUniform = new Texture{ TEXTURE_DIRT_UNIFORM, GL_RGBA };

		stoneTextureUniform = new Texture{ TEXTURE_STONE_UNIFORM, GL_RGBA };

		logTextureSide = new Texture{ TEXTURE_LOG_SIDE, GL_RGBA };
		logTextureRest = new Texture{ TEXTURE_LOG_REST, GL_RGBA };

		Entity* block1;
		Entity* block2;
		Entity* block3;
		Entity* block4;

		block1 = EntityContainer::Get().RegisterEntity();
		block1->RegisterComponent(new BlockComponent(dirtTextureUniform, defaultShader));
		block1->GetTransform().Scale(VECTOR3_HALVE_SCALE);

		block2 = EntityContainer::Get().RegisterEntity();
		block2->RegisterComponent(new BlockComponent(stoneTextureUniform, defaultShader));
		block2->GetTransform().Scale(VECTOR3_HALVE_SCALE);
		block2->GetTransform().Translate(VECTOR3_X);

		block3 = EntityContainer::Get().RegisterEntity();
		block3->RegisterComponent(new BlockComponent(logTextureSide, logTextureRest, defaultShader));
		block3->GetTransform().Scale(VECTOR3_HALVE_SCALE);
		block3->GetTransform().Translate(-VECTOR3_X);

		block4 = EntityContainer::Get().RegisterEntity();
		block4->RegisterComponent(new BlockComponent(grassTextureSide, grassTextureTop, grassTextureBottom, defaultShader));
		block4->GetTransform().Scale(VECTOR3_HALVE_SCALE);
		block4->GetTransform().Translate(VECTOR3_Y);
	}
}
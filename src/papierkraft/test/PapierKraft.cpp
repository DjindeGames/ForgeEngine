#include "PapierKraft.h"

#include "engine/3d/MeshComponent.h"
#include "engine/core/Entity.h"
#include "engine/core/Game.h"
#include "engine/misc/Color.h"
#include "engine/misc/Texture.h"
#include "engine/shader/Shader.h"
#include "engine/shader/ShaderUtils.h"

#include "Block.h"

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
		Game game{};
		game.Init("PapierKraft", 800, 600);
		game.SetUpdateCallback(Update);
		game.SetTerminationConditionCallback(ShouldTerminate);

		PerformTests();

		BuildMeshes();

		game.HandleProcess();
		
		delete(defaultShader);
		delete(grassTextureSide);
		delete(grassTextureTop);
		delete(grassTextureBottom);
		delete(dirtTextureUniform);

		return 0;
	}

	void Update(float dT)
	{
		ProcessInput();
		ShaderUtils::SetBackgroundColor(COLOR_BLACK);
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

	void BuildMeshes()
	{
		defaultShader = new Shader{ TEXTURED_VERTEX_SHADER_PATH, TEXTURED_FRAGMENT_SHADER_PATH };

		grassTextureSide = new Texture{ TEXTURE_GRASS_SIDE, GL_RGBA };
		grassTextureTop = new Texture{ TEXTURE_GRASS_TOP, GL_RGBA };
		grassTextureBottom = new Texture{ TEXTURE_GRASS_BOTTOM, GL_RGBA };

		dirtTextureUniform = new Texture{ TEXTURE_DIRT_UNIFORM, GL_RGBA };

		Block::Create(grassTextureSide, grassTextureTop, grassTextureBottom, defaultShader);
		//Block::Create(dirtTextureUniform, defaultShader);
	}
}
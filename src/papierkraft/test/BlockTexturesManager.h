#pragma once

#include "engine/core/Manager.h"

#include <vector>

using namespace ForgeEngine;

namespace ForgeEngine
{
	class Texture;
}

namespace PapierKraft
{
	#define TEXTURE_GRASS_SIDE		"assets\\textures\\blocks\\grass\\grass_side.png"
	#define TEXTURE_GRASS_TOP		"assets\\textures\\blocks\\grass\\grass_top.png"
	#define TEXTURE_GRASS_BOTTOM	"assets\\textures\\blocks\\grass\\grass_bottom.png"

	#define TEXTURE_DIRT_UNIFORM	"assets\\textures\\blocks\\dirt\\dirt_uniform.png"

	#define TEXTURE_STONE_UNIFORM	"assets\\textures\\blocks\\stone\\stone_uniform.png"

	#define TEXTURE_LOG_SIDE		"assets\\textures\\blocks\\log\\log_side.png"
	#define TEXTURE_LOG_REST		"assets\\textures\\blocks\\log\\log_top.png"

	template<typename T>
	class BlockTextureManager : public Manager<T>
	{
		using Mother = Manager<T>;

		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		private:
			std::vector<Texture*> m_RegisteredTextures{};

		/************************************/
		/**************METHODS***************/
		/************************************/

		protected:
			virtual void OnDestroy() override;
	};
}
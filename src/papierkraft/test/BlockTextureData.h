#pragma once

#include "engine/core/Object.h"
#include "engine/misc/Texture.h"

#include <memory>
#include <string>

using namespace ForgeEngine;

namespace PapierKraft
{
	#define TEXTURE_GRASS_SIDE		"assets\\textures\\blocks\\grass\\grass_side.png"
	#define TEXTURE_GRASS_TOP		"assets\\textures\\blocks\\grass\\grass_top.png"
	#define TEXTURE_GRASS_BOTTOM	"assets\\textures\\blocks\\grass\\grass_bottom.png"

	#define TEXTURE_DIRT_UNIFORM	"assets\\textures\\blocks\\dirt\\dirt_uniform.png"

	#define TEXTURE_STONE_UNIFORM	"assets\\textures\\blocks\\stone\\stone_uniform.png"

	#define TEXTURE_LEAVES_UNIFORM	"assets\\textures\\blocks\\leaves\\leaves_uniform.png"

	#define TEXTURE_LOG_SIDE		"assets\\textures\\blocks\\log\\log_side.png"
	#define TEXTURE_LOG_REST		"assets\\textures\\blocks\\log\\log_top.png"

	class BlockTextureData : Object
	{
		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		private:
			std::shared_ptr<Texture> m_SideTexture{};
			std::shared_ptr<Texture> m_TopTexture{};
			std::shared_ptr<Texture> m_BottomTexture{};

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			BlockTextureData(std::string sideTexture, std::string topTexture, std::string bottomTexture);
			BlockTextureData(std::string sideTexture, std::string topBottomTexture);
			BlockTextureData(std::string uniformTexture);
			~BlockTextureData() {}

			Texture* GetSideTexture() const { return m_SideTexture.get(); }
			Texture* GetTopTexture() const { return m_TopTexture.get(); }
			Texture* GetBottomTexture() const { return m_BottomTexture.get(); }
	};
}

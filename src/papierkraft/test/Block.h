#pragma once

#include "engine/core/Entity.h"

using namespace ForgeEngine;

namespace ForgeEngine
{
	class Shader;
	class Texture;
}

namespace PapierKraft
{
	#define TEXTURE_GRASS_SIDE "assets\\textures\\blocks\\grass\\grass_side.png"
	#define TEXTURE_GRASS_TOP "assets\\textures\\blocks\\grass\\grass_top.png"
	#define TEXTURE_GRASS_BOTTOM "assets\\textures\\blocks\\grass\\grass_bottom.png"

	#define TEXTURE_DIRT_UNIFORM "assets\\textures\\blocks\\dirt\\dirt_uniform.png"

	class Block : public Entity
	{
		using Mother = Entity;
		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		private:

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			static Block* Create(Texture* sideTexture, Texture* topTexture, Texture* bottomTexture, Shader* shader);
			static Block* Create(Texture* uniformTexture, Shader* shader);

		protected:
			Block(Texture* sideTexture, Texture* topTexture, Texture* bottomTexture, Shader* shader);
	};
}
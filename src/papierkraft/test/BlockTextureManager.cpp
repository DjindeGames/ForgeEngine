#include "BlockTextureManager.h"

#include "papierkraft/test/BlockComponent.h"

#include "engine/misc/Texture.h"

namespace PapierKraft
{
	BlockTextureManager::BlockTextureManager() :
		Mother()
	{
		//GRASS
		m_RegisteredTextures[EBlockType::Grass] = std::make_unique<BlockTextureData>(
			TEXTURE_GRASS_SIDE,
			TEXTURE_GRASS_TOP,
			TEXTURE_GRASS_BOTTOM
		);

		//DIRT
		m_RegisteredTextures[EBlockType::Dirt] = std::make_unique<BlockTextureData>(
			TEXTURE_DIRT_UNIFORM
		);

		//STONE
		m_RegisteredTextures[EBlockType::Stone] = std::make_unique<BlockTextureData>(
			TEXTURE_STONE_UNIFORM
		);

		//WOODLOG
		m_RegisteredTextures[EBlockType::Woodlog] = std::make_unique<BlockTextureData>(
			TEXTURE_LOG_SIDE, 
			TEXTURE_LOG_REST
		);
	}
}
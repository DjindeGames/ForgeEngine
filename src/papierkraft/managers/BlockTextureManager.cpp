#include "BlockTextureManager.h"

#include "engine/misc/Texture.h"
#include "papierkraft/components/BlockComponent.h"

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

		//SAND
		m_RegisteredTextures[EBlockType::Sand] = std::make_unique<BlockTextureData>(
			TEXTURE_SAND_UNIFORM
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

		//LEAVES
		m_RegisteredTextures[EBlockType::Leaves] = std::make_unique<BlockTextureData>(
			TEXTURE_LEAVES_UNIFORM
		);
	}

	BlockTextureData* BlockTextureManager::GetTextureDataByBlockType(EBlockType blockType) const
	{
		auto it = m_RegisteredTextures.find(blockType);
		return (it != m_RegisteredTextures.end()) ? (*it).second.get() : nullptr;
	}
}
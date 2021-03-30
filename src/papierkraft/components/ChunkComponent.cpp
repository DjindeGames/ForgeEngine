#include "ChunkComponent.h"

#include "engine/core/ForgeEngine.h"
#include "papierkraft/components/BlockComponent.h"
#include "system/math/MathUtils.h"

namespace PapierKraft
{
	ChunkComponent::ChunkComponent(EBiomeType biomeType, Vector3 position) :
		Mother(),
		m_BiomeType(biomeType)
	{
		for (float x = -(CHUNK_WIDTH / 2) ; x < (CHUNK_WIDTH / 2); x++)
		{
			for (float y = 0 ; y < CHUNK_HEIGHT ; y++)
			{
				for (float z = -(CHUNK_WIDTH / 2); z < (CHUNK_WIDTH / 2); z++)
				{
					Entity* block = EntityContainer::Get()->RegisterEntity();
					block->RegisterComponent(new BlockComponent(ComputeBlockType(y)));
					block->GetTransform()->SetPosition(Vector3{ position.x + x, position.y + y, position.z + z});
				}
			}
		}
	}

	EBlockType ChunkComponent::ComputeBlockType(float yCoordinate)
	{
		EBlockType blockType;

		if (ForgeMaths::IsBetween(yCoordinate, static_cast<float>(CHUNK_HEIGHT - DIRT_LAYER_HEIGHT), static_cast<float>(CHUNK_HEIGHT - 1)))
		{
			if (yCoordinate == CHUNK_HEIGHT - 1)
			{
				blockType = EBlockType::Woodlog;
			}
			else
			{
				blockType = EBlockType::Dirt;
			}
		}
		else
		{
			blockType = EBlockType::Sand;
		}

		return blockType;
	}
}
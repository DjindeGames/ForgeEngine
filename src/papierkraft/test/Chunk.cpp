#include "Chunk.h"

#include "papierkraft/test/BlockComponent.h"

#include "engine/core/Entity.h"
#include "system/math/MathUtils.h"

namespace PapierKraft
{
	Chunk::Chunk(EBiomeType biomeType, Vector3 position) :
		Mother(),
		m_BiomeType(biomeType)
	{
		for (float x = -(CHUNK_WIDTH / 2) ; x < (CHUNK_WIDTH / 2); x++)
		{
			for (float y = -(CHUNK_WIDTH / 2); y < (CHUNK_WIDTH / 2); y++)
			{
				for (float z = -(CHUNK_HEIGHT / 2); z < (CHUNK_HEIGHT / 2); z++)
				{
					Entity* block = EntityContainer::Get()->RegisterEntity();
					block->RegisterComponent(new BlockComponent(ComputeBlockType(y)));
					block->SetPosition(Vector3{ position.x + x,  position.y + y, position.z + z});
				}
			}
		}
	}

	EBlockType Chunk::ComputeBlockType(float yCoordinate)
	{
		EBlockType blockType;

		if (ForgeMaths::IsBetween(yCoordinate, CHUNK_WIDTH / 2.f - DIRT_LAYER_HEIGHT, CHUNK_WIDTH / 2.f - 1))
		{
			if (yCoordinate == CHUNK_WIDTH / 2 - 1)
			{
				blockType = EBlockType::Grass;
			}
			else
			{
				blockType = EBlockType::Dirt;
			}
		}
		else
		{
			blockType = EBlockType::Stone;
		}

		return blockType;
	}
}
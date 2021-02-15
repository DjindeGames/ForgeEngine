#pragma once

#include "engine/core/Object.h"
#include "system/math/Vector3.h"

using namespace ForgeEngine;

namespace PapierKraft
{
	#define CHUNK_WIDTH 8
	#define CHUNK_HEIGHT 8

	#define DIRT_LAYER_HEIGHT 3

	enum class EBiomeType
	{
		Plain = 0,
		Desert,
		Forest,
		Count
	};

	enum class EBlockType;

	class Chunk : Object
	{
		using Mother = Object;

		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		private:
			EBiomeType m_BiomeType;

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			Chunk(EBiomeType biomeType, Vector3 position);
			
			EBlockType ComputeBlockType(float yCoordinate);
	};
}
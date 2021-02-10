#pragma once

#include "engine/core/Manager.h"
#include "papierkraft/test/BlockTextureData.h"

#include <unordered_map>

using namespace ForgeEngine;

namespace PapierKraft
{
	enum class EBlockType;

	class BlockTextureManager : public Manager
	{
		using Mother = Manager;

		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		private:
			std::unordered_map<EBlockType, std::unique_ptr<BlockTextureData>> m_RegisteredTextures{};

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			BlockTextureManager();

			BlockTextureData* GetTextureDataByBlockType(EBlockType blockType) const;
	};
}
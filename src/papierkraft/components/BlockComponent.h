#pragma once

#include "engine/core/Component.h"

namespace ForgeEngine
{
	class Shader;
	class Texture;
}

using namespace ForgeEngine;

namespace PapierKraft
{
	class BlockTextureData;

	enum class EBlockType
	{
		Dirt = 0,
		Grass,
		Stone,
		Woodlog,
		Sand,
		Count
	};

	class BlockComponent : public Component
	{
		using Mother = Component;

		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		private:
			EBlockType m_BlockType;
			BlockTextureData* m_TextureData{};
			Shader* m_Shader{};

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			BlockComponent(EBlockType blockType);

		protected:
			virtual bool OnPreInit() override;
	};
}
#pragma once

#include "engine/core/Component.h"

using namespace ForgeEngine;

namespace ForgeEngine
{
	class Shader;
	class Texture;
}

namespace PapierKraft
{
	class BlockComponent : public Component
	{
		using Mother = Component;

		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		private:
			Texture* m_SideTexture{};
			Texture* m_TopTexture{};
			Texture* m_BottomTexture{};

			Shader* m_Shader{};

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			BlockComponent(Texture* sideTexture, Texture* topTexture, Texture* bottomTexture, Shader* shader);
			BlockComponent(Texture* sideTexture, Texture* restTexture, Shader* shader);
			BlockComponent(Texture* uniformTexture, Shader* shader);

		protected:
			virtual void OnInit() override;
	};
}
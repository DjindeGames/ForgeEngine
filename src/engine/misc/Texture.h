#pragma once

#include <engine/core/CoreEngine.h>

namespace ForgeEngine
{
	#define TEXTURE_RESOLUTION 16

	#define TEXTURE_DIRT_SIDE "assets\\textures\\blocks\\dirt\\dirt_side.png"

	class Texture
	{
		/************************************/
		/************ATTRIBUTES**************/
		/************************************/
		private:
			GL_ID m_GLTexture{};

			int m_Width{};
			int m_Height{};
			int m_Channels{};

	private:

		/************************************/
		/**************METHODS***************/
		/************************************/

	public:
		Texture(const char* texturePath);
		~Texture();

		void Use();
	};
}

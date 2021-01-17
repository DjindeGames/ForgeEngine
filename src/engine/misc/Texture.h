#pragma once

#include <engine/core/CoreEngine.h>

#include <glad/glad.h>

namespace ForgeEngine
{
	#define TEXTURE_RESOLUTION 16

	#define MISSING_TEXTURE "assets\\textures\\default\\default.png"

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
		Texture(const char* texturePath, unsigned int rgbaMode = GL_RGB, bool flip = true);
		~Texture();

		GL_ID GetGLTexture() const { return m_GLTexture; }
		void Use();
	};
}

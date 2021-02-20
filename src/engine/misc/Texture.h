#pragma once

#include "engine/core/Defines.h"
#include "engine/core/Object.h""
#include "engine/core/OpenGL.h"

namespace ForgeEngine
{
	#define TEXTURE_RESOLUTION 16

	#define MISSING_TEXTURE "assets\\textures\\default\\default.png"

	class Texture : Object
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
		Texture(const char* texturePath, unsigned int rgbaMode = GL_RGBA, bool flip = true);
		~Texture();

		int GetWidth() const { return m_Width; }
		int GetHeight() const { return m_Height; }

		GL_ID GetGLTexture() const { return m_GLTexture; }
		void Use();
	};
}

#pragma once

#include "engine/core/Defines.h"
#include "engine/core/LoadableResource.h"
#include "engine/core/OpenGL.h"

namespace ForgeEngine
{
	class Texture : LoadableResource
	{
		using Mother = LoadableResource;

		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		private:
			GL_ID m_GLTexture{};

			int m_Width{};
			int m_Height{};
			int m_Channels{};

            const char* m_Name;

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			Texture(const char* texturePath, unsigned int rgbaMode = GL_RGBA, bool flip = true);
			Texture(void* data, unsigned int width, unsigned int height);
			~Texture();

            bool IsValid() const override { return m_GLTexture; }

			int GetWidth() const { return m_Width; }
			int GetHeight() const { return m_Height; }
            const char* GetName() const { return m_Name; }

			GL_ID GetGLTexture() const { return m_GLTexture; }
			void Use();
	};
}

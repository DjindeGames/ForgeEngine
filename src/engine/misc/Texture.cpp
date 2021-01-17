#include "Texture.h"

#include <iostream>

#include <stb_image/stb_image.h>

namespace ForgeEngine
{
	Texture::Texture(const char* texturePath, unsigned int rgbaMode/*= GL_RGB*/, bool flip/* = true*/)
	{
		stbi_set_flip_vertically_on_load(flip);
		unsigned char* data = stbi_load(texturePath, &m_Width, &m_Height, &m_Channels, 0);
		stbi_set_flip_vertically_on_load(false);

		if (data)
		{
			glGenTextures(1, &m_GLTexture);
			glBindTexture(GL_TEXTURE_2D, m_GLTexture);

			// set the texture wrapping/filtering options (on the currently bound texture object)
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, rgbaMode, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Could not load texture!" << std::endl;
		}
		
		stbi_image_free(data);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_GLTexture);
	}

	void Texture::Use()
	{
		glBindTexture(GL_TEXTURE_2D, m_GLTexture);
	}
}
#include "Texture.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image/stb_image.h>

namespace ForgeEngine
{
	Texture::Texture(const char* texturePath)
	{
		unsigned char* data = stbi_load(texturePath, &m_Width, &m_Height, &m_Channels, 0);

		if (data)
		{
			glGenTextures(1, &m_GLTexture);
			glBindTexture(GL_TEXTURE_2D, m_GLTexture);

			// set the texture wrapping/filtering options (on the currently bound texture object)
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_POINT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_POINT);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
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
		//glDeleteTextures(1, &m_GLTexture);
	}

	void Texture::Use()
	{
		glBindTexture(GL_TEXTURE_2D, m_GLTexture);
	}
}
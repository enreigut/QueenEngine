#include "Texture.h"

#include <GL/glew.h>

namespace Queen
{
	namespace Renderer
	{
		Texture::Texture()
		{

		}

		Texture::~Texture()
		{

		}

		void Texture::GenerateTexture()
		{
			glGenTextures(1, &m_texture);
		}

		void Texture::BindTexture()
		{
			glBindTexture(GL_TEXTURE_2D, m_texture);
		}

		void Texture::TexImage2D(int&& width, int&& height )
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}

		void Texture::FrameBufferTexture()
		{
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0);
		}

		void Texture::UnbindTexture()
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}
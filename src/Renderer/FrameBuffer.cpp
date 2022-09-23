#include "FrameBuffer.h"

#include <GL/glew.h>
#include <exception>

namespace Queen
{
	namespace Renderer
	{
		FrameBuffer::FrameBuffer()
		{

		}

		FrameBuffer::~FrameBuffer()
		{
			glDeleteFramebuffers(1, &m_fbo);
			glDeleteTextures(1, &m_color);
			glDeleteTextures(1, &m_depth);
		}

		void FrameBuffer::Bind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
		}

		void FrameBuffer::Unbind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		void FrameBuffer::CreateFrameBuffer(float width, float height)
		{
			if (m_fbo)
			{
				glDeleteFramebuffers(1, &m_fbo);
				glDeleteTextures(1, &m_color);
				glDeleteTextures(1, &m_depth);
			}

			// FrameBuffer
			glCreateFramebuffers(1, &m_fbo);

			// Color Attachment
			glCreateTextures(GL_TEXTURE_2D, 1, &m_color);

			// Depth Attachment
			glCreateTextures(GL_TEXTURE_2D, 1, &m_depth);

			// Select Framebuffer
			glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
			
			// Add Color attachment to Framebuffer
			glBindTexture(GL_TEXTURE_2D, m_color);
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RGBA8,
				(GLsizei) width,
				(GLsizei) height,
				0,
				GL_RGBA,
				GL_UNSIGNED_BYTE,
				nullptr
			);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_color, 0);

			// Add Depth Attachment to Framebuffer
			glBindTexture(GL_TEXTURE_2D, m_depth);
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_DEPTH24_STENCIL8,
				(GLsizei) width,
				(GLsizei) height,
				0,
				GL_DEPTH_STENCIL,
				GL_UNSIGNED_INT_24_8,
				nullptr
			);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_depth, 0);

			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
				throw std::exception("Framebuffer incomplete");
			
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}
}
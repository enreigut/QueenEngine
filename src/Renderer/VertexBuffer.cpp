#include "VertexBuffer.h"

namespace Queen
{
	namespace Renderer
	{
		VertexBuffer::VertexBuffer()
		{

		}

		VertexBuffer::~VertexBuffer()
		{

		}

		void VertexBuffer::GenerateBuffer()
		{
			glGenBuffers(1, &m_bufferId);
		}

		void VertexBuffer::BindBuffer()
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_bufferId);
		}

		void VertexBuffer::UnbindBuffer()
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void VertexBuffer::DeleteBuffer()
		{
			glDeleteBuffers(1, &m_bufferId);
		}
	}
}
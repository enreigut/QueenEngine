#include "ElementBuffer.h"

namespace Queen
{
	namespace Renderer
	{
		ElementBuffer::ElementBuffer()
		{

		}

		ElementBuffer::~ElementBuffer()
		{

		}

		void ElementBuffer::GenerateBuffer()
		{
			glGenBuffers(1, &m_bufferId);
		}

		void ElementBuffer::BindBuffer()
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferId);
		}

		void ElementBuffer::UnbindBuffer()
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		void ElementBuffer::DeleteBuffer()
		{
			glDeleteBuffers(1, &m_bufferId);
		}

		void ElementBuffer::BindData(std::vector<unsigned int>& data)
		{
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(unsigned int), &data[0], GL_STATIC_DRAW);
		}
	}
}
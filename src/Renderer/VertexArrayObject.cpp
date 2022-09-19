#include "VertexArrayObject.h"

namespace Queen
{
	namespace Renderer
	{
		VertexArrayObject::VertexArrayObject()
		{

		}

		VertexArrayObject::~VertexArrayObject()
		{

		}

		void VertexArrayObject::GenerateBuffer()
		{
			glGenVertexArrays(1, &m_bufferId);
		}

		void VertexArrayObject::BindBuffer()
		{
			glBindVertexArray(m_bufferId);
		}

		void VertexArrayObject::UnbindBuffer()
		{
			glBindVertexArray(0);
		}

		void VertexArrayObject::DeleteBuffer()
		{
			glDeleteVertexArrays(1, &m_bufferId);
		}
	}
}
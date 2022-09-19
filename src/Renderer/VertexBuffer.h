#pragma once

#include "Buffer.h"
#include <vector>
#include <GL/glew.h>

namespace Queen
{
	namespace Renderer
	{
		class VertexBuffer : public Buffer
		{
		public:
			VertexBuffer();
			~VertexBuffer();

			// Getters

			// Setters

			// Derived
			void GenerateBuffer() override;
			void BindBuffer() override;
			void UnbindBuffer() override;
			void DeleteBuffer() override;
			
			// Forced to declare template functions in h file
			template<typename T>
			void BindData(std::vector<T>& data)
			{
				glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(T), &data[0], GL_STATIC_DRAW);
			}

		private:

		};
	}
}
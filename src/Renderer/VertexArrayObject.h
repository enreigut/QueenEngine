#pragma once

#include "Buffer.h"

#include <GL/glew.h>

namespace Queen
{
	namespace Renderer
	{
		class VertexArrayObject: public Buffer
		{
		public:
			VertexArrayObject();
			~VertexArrayObject();

			// Getters

			// Setters

			// Derived
			void GenerateBuffer() override;
			void BindBuffer() override;
			void UnbindBuffer() override;
			void DeleteBuffer() override;

		private:

		};
	}
}
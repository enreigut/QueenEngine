#pragma once

#include "Buffer.h"
#include <vector>
#include <GL/glew.h>

namespace Queen
{
	namespace Renderer
	{
		class ElementBuffer : public Buffer
		{
		public:
			ElementBuffer();
			~ElementBuffer();

			// Getters

			// Setters

			// Derived
			void GenerateBuffer() override;
			void BindBuffer() override;
			void UnbindBuffer() override;
			void DeleteBuffer() override;
			void BindData(std::vector<unsigned int>& data);

		private:

		};
	}
}
#pragma once

namespace Queen
{
	namespace Renderer
	{
		class Buffer
		{
		public:
			Buffer() {};
			~Buffer() {};

			// Getter

			// Setter

			// Derived
			virtual void GenerateBuffer() = 0;
			virtual void BindBuffer() = 0;
			virtual void UnbindBuffer() = 0;
			virtual void DeleteBuffer() = 0;

		protected:
			unsigned int m_bufferId = 0;

		};
	}
}
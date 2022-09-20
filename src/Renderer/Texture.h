#pragma once

namespace Queen
{
	namespace Renderer
	{
		class Texture
		{
		public:
			Texture();
			~Texture();

			// Getters
			inline unsigned int GetTexture() const { return m_texture; }

			// Setters

			// Derived
			void GenerateTexture();
			void BindTexture();
			void TexImage2D(int&& width, int&& height);
			void FrameBufferTexture();
			void UnbindTexture();

		private:
			unsigned int m_texture = 0;

		};
	}
}

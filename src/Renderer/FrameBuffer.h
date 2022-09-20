#pragma once

namespace Queen
{
	namespace Renderer
	{
		class FrameBuffer
		{
		public:
			FrameBuffer();
			~FrameBuffer();

			// Getters
			inline unsigned int GetColorAttachment() const { return m_color; }
			inline unsigned int GetDepthAttachment() const { return m_depth; }

			// Setters

			// Derived
			void Bind();
			void Unbind();
			void CreateFrameBuffer(float width, float height);

		private:
			unsigned int m_fbo = 0;
			unsigned int m_color = 0;
			unsigned int m_depth = 0;
		};
	}
}

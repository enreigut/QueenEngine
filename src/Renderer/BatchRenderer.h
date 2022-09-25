#pragma once

#include <GLM/glm.hpp>
#include "../Scenes/Scene.h"
#include "RenderingBufferData.h"

namespace Queen
{
	namespace Renderer
	{
		struct RenderStats
		{
			unsigned int drawCalls = 0;
			unsigned int vertices = 0;
			unsigned int indices = 0;
		};

		class BatchRenderer
		{
		public:
			BatchRenderer();
			~BatchRenderer();

			// Getters
			inline RenderStats GetRenderStats() { return m_renderStats; }

			// Setters

			// Derived
			void LoadSceneVertexData(Scene& scene);
			void CreateBuffers();
			void OnUpdate();
			void OnUpdate(Scene& scene);

		private:
			std::vector<RenderingBufferData> m_data;
			RenderStats m_renderStats;
			std::vector<unsigned int> m_vbos;
			std::vector<unsigned int> m_ebos;
			std::vector<unsigned int> m_vaos;
		};
	}
}

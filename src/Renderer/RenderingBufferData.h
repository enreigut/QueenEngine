#pragma once

#include <vector>

namespace Queen
{
	namespace Renderer
	{
		class RenderingBufferData
		{
		public:
			RenderingBufferData();
			~RenderingBufferData();

			// Getters
			inline size_t GetMaxBufferSize() const { return m_maxDataSize; }
			inline size_t GetRemaningVerticesSize() const { return m_maxDataSize - m_currentSize; }
			inline size_t GetFilledSize() const { return m_currentSize; }
			inline std::vector<float> GetVertices() const { return m_vertices; }
			inline std::vector<unsigned int> GetIndices() const { return m_indices; }

			// Setters

			// Derived
			bool AddVertices(std::vector<float>& vertices);
			bool AddVertices(float& vertices);
			void AddIndices(std::vector<unsigned int>& indices);
			bool AddData(std::vector<float>& vertices, std::vector<unsigned int>& indices);
			void IncreaseMaxDataSize();

		private:
			size_t m_maxDataSize = 10000;
			size_t m_currentSize = 0;
			size_t m_prevSize = 0;
			bool isFirst = true;
			std::vector<float> m_vertices;
			std::vector<unsigned int> m_indices;
		};
	}
}
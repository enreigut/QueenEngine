#pragma once

#include "../Scenes/Scene.h"
#include <GLM/glm.hpp>

namespace Queen
{
	namespace Renderer
	{

		class RenderingBufferData
		{
		public:
			RenderingBufferData()
			{
				m_vertices.reserve(m_maxDataSize);
			}
			~RenderingBufferData() {}

			// Getters
			inline size_t GetRemaningVerticesSize() const { return m_maxDataSize - m_currentSize; }
			inline size_t GetFilledSize() const { return m_currentSize; }
			inline std::vector<float> GetVertices() const { return m_vertices; }
			inline std::vector<unsigned int> GetIndices() const { return m_indices; }

			// Setters

			// Derived
			bool AddVertices(std::vector<float>& vertices)
			{
				if (GetRemaningVerticesSize() > 0 && GetRemaningVerticesSize() >= vertices.size())
				{
					m_vertices.insert(
						m_vertices.end(),
						vertices.begin(),
						vertices.end()
					);
					m_prevSize = m_currentSize;
					m_currentSize += vertices.size();
					return true;
				}
				return false;
			}

			bool AddVertices(float& vertices)
			{
				if (GetRemaningVerticesSize() >= 1)
				{
					m_vertices.push_back(vertices);
					m_currentSize += 1;
					return true;
				}
				return false;
			}

			void AddIndices(std::vector<unsigned int>& indices)
			{
				if (isFirst)
				{
					m_indices.insert(
						m_indices.end(),
						indices.begin(),
						indices.end()
					);
				}
				else
				{
					for (int i = 0; i < indices.size(); i++)
					{
						m_indices.push_back(indices[i] + (int)m_prevSize/3);
					}
				}
			}

			bool AddData(std::vector<float>& vertices, std::vector<unsigned int>& indices)
			{
				if (!AddVertices(vertices))
					return false;

				AddIndices(indices);
				isFirst = false;
				return true;
			}
			
		private:
			size_t m_maxDataSize = 3000;
			size_t m_currentSize = 0;
			size_t m_prevSize = 0;
			bool isFirst = true;
			std::vector<float> m_vertices;
			std::vector<unsigned int> m_indices;
		};

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

			unsigned int m_vbo;
			unsigned int m_ebo;
			unsigned int m_vao;
		};
	}
}

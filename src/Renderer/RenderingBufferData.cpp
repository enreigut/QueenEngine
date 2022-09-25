#include "RenderingBufferData.h"

namespace Queen
{
	namespace Renderer
	{
		RenderingBufferData::RenderingBufferData()
		{
			m_vertices.reserve(m_maxDataSize);
		}

		RenderingBufferData::~RenderingBufferData()
		{

		}

		bool RenderingBufferData::AddVertices(std::vector<float>& vertices)
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

		bool RenderingBufferData::AddVertices(float& vertices)
		{
			if (GetRemaningVerticesSize() >= 1)
			{
				m_vertices.push_back(vertices);
				m_currentSize += 1;
				return true;
			}
			return false;
		}

		void RenderingBufferData::AddIndices(std::vector<unsigned int>& indices)
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
					m_indices.push_back(indices[i] + (int)m_prevSize / 3);
				}
			}
		}

		bool RenderingBufferData::AddData(std::vector<float>& vertices, std::vector<unsigned int>& indices)
		{
			if (!AddVertices(vertices))
				return false;

			AddIndices(indices);
			isFirst = false;
			return true;
		}

		void RenderingBufferData::IncreaseMaxDataSize()
		{
			m_maxDataSize += m_maxDataSize;
		}
	}
}
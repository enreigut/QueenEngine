#include "BatchRenderer.h"

#include <GL/glew.h>

namespace Queen
{
	namespace Renderer
	{
		BatchRenderer::BatchRenderer()
		{

		}

		BatchRenderer::~BatchRenderer()
		{

		}

		void BatchRenderer::LoadSceneVertexData(Scene& scene)
		{
			ECS::Entity* e = nullptr;

			unsigned int count = 0;
			unsigned int prevSize = 0;

			for (std::pair<const char*, ECS::Entity*> data: scene.GetEntities())
			{
				e = data.second;
				ECS::Model* m = e->GetComponent<ECS::Model>();
				
				if (m != nullptr)
				{
					// If not data buffer created we create one
					if (m_data.size() <= 0)
					{
						RenderingBufferData bufferData;
						m_data.push_back(bufferData);
						while(!m_data.back().AddData(m->p_vertices, m->p_indices))
						{
							m_data.back().IncreaseMaxDataSize();
						}
					}
					else
					{
						bool couldAdd = false;

						for (int i = 0; i < m_data.size(); i++)
						{
							if (m_data[i].AddData(m->p_vertices, m->p_indices))
							{
								couldAdd = true;
								break;
							}
						}

						if (!couldAdd)
						{
							RenderingBufferData bufferData;
							m_data.push_back(bufferData);
							while (!m_data.back().AddData(m->p_vertices, m->p_indices))
							{
								m_data.back().IncreaseMaxDataSize();
							}
						}
					}
				}
			}
		}

		void BatchRenderer::CreateBuffers()
		{
			m_renderStats = { 0 , 0, 0 };

			for (int i = 0; i < m_data.size(); i++)
			{
				unsigned int vbo;
				unsigned int ebo;
				unsigned int vao;

				glCreateVertexArrays(1, &vao);
				glBindVertexArray(vao);

				glCreateBuffers(1, &vbo);
				glBindBuffer(GL_ARRAY_BUFFER, vbo);
				glBufferData(GL_ARRAY_BUFFER, m_data[i].GetVertices().size() * sizeof(float), &m_data[i].GetVertices()[0], GL_STATIC_DRAW);
				
				m_renderStats.vertices += (unsigned int) m_data[i].GetVertices().size();

				glCreateBuffers(1, &ebo);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_data[i].GetIndices().size() * sizeof(unsigned int), &m_data[i].GetIndices()[0], GL_STATIC_DRAW);

				m_renderStats.indices += (unsigned int) m_data[i].GetIndices().size();

				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void*)0);
				glEnableVertexAttribArray(0);

				m_vbos.push_back(vbo);
				m_ebos.push_back(ebo);
				m_vaos.push_back(vao);

				glBindBuffer(GL_ARRAY_BUFFER, 0);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
				
				glBindVertexArray(0);
			}


			m_renderStats.drawCalls = (unsigned int) m_data.size();
		}

		void BatchRenderer::OnUpdate()
		{
			/*glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
			glBufferSubData(GL_ARRAY_BUFFER, 0, m_vertices.size() * sizeof(float), &m_vertices[0]);*/

			for (int i = 0; i < m_data.size(); i++)
			{
				glBindVertexArray(m_vaos[i]);
				glDrawElements(
					GL_TRIANGLES,
					(GLsizei)m_data[i].GetIndices().size(),
					GL_UNSIGNED_INT,
					0
				);
			}
		}

		void BatchRenderer::OnUpdate(Scene& scene)
		{
			
		}
	}
}
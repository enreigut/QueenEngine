#include "Application.h"

#include <exception>
#include "../Renderer/Shader.h"
#include "../Renderer/VertexBuffer.h"
#include "../Renderer/ElementBuffer.h"
#include "../Renderer/VertexArrayObject.h"
#include <GLM/glm.hpp>
#include <GLM/ext.hpp>

namespace Queen
{
	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::StartManagers()
	{
		try
		{
			// Window Manager
			if(!m_windowManager)
				m_windowManager = new Managers::WindowManager();

			m_windowManager->Start();
		}
		catch (std::exception e)
		{
			// TODO: LOG ERROR

			exit(-1);
		}
	}

	void Application::Shutdown()
	{
		if (m_windowManager != nullptr)
		{	
			try
			{
				m_windowManager->Shutdown();
				delete(m_windowManager);
			}
			catch (std::exception e)
			{
				// TODO: LOG ERROR
			}
		}
	}

	void Application::CreateApplication(const char* name)
	{
		if (!m_windowManager)
			throw std::exception("Window Manager is null!");

		m_windowManager->CreateWindow(name);
	}

	void Application::Run()
	{
		if (!m_windowManager)
			throw std::exception("Window Manager is null!");

		// TODO: REMOVE JUST TESTING

		std::vector<float> data = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
			-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
			0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
		};

		std::vector<unsigned int> indices = {
			0, 3, 1,
			0, 2, 3
		};
		
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -1.0f));
	
		Renderer::VertexArrayObject vao;
		Renderer::VertexBuffer vbo;
		Renderer::ElementBuffer ebo;

		vao.GenerateBuffer();
		vbo.GenerateBuffer();
		ebo.GenerateBuffer();

		vao.BindBuffer();

		vbo.BindBuffer();
		vbo.BindData(data);

		ebo.BindBuffer();
		ebo.BindData(indices);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
		glEnableVertexAttribArray(1);

		vao.UnbindBuffer();

		Renderer::Shader shader;
		shader.CreateProgram(
			"D:/Dev/Projects/QueenEngine/Assets/Shaders/vertex.vert",
			"D:/Dev/Projects/QueenEngine/Assets/Shaders/fragment.frag"
		);

		glViewport(0, 0, m_windowManager->GetWidth(), m_windowManager->GetHeight());

		while (!m_windowManager->ShouldWindowClose())
		{
			m_timer.Start();

			m_windowManager->EarlyUpdate();

			glm::mat4 projection = glm::perspective(45.0f, m_windowManager->GetAspectRatio(), 0.0f, 10.0f);

			shader.UseProgram();

			shader.SetUniformLocationMat4f("model", model);
			shader.SetUniformLocationMat4f("view", viewMatrix);
			shader.SetUniformLocationMat4f("projection", projection);

			vao.BindBuffer();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

			m_windowManager->LateUpdate();
			
			m_timer.Stop();
			m_timer.DurationInMs();

			std::printf("%f\n", m_timer.p_durationInMs);
		}
	}
}
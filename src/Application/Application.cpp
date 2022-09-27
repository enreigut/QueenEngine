#include "Application.h"

#include <exception>
#include <GLM/glm.hpp>
#include <GLM/ext.hpp>

// TODO: Remove
#include "../Renderer/Shader.h"
#include "../Renderer/VertexBuffer.h"
#include "../Renderer/ElementBuffer.h"
#include "../Renderer/FrameBuffer.h"
#include "../Renderer/VertexArrayObject.h"
#include "../ECS/Entity.h"
#include "../ECS/Component.h"
#include "../ECS/System.h"

#include <thread>

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

			// ImGUi Manager
			if (!m_imGuiManager)
				m_imGuiManager = new Managers::ImGuiManager();

			m_imGuiManager->Start();

			// Scene Manager
			if (!m_sceneManager)
				m_sceneManager = new Managers::SceneManager();

			m_sceneManager->Start();

			// Renderer
			m_batchRenderer = new Renderer::BatchRenderer();

			// Viewport
			m_viewport = new Viewport;
		}
		catch (std::exception e)
		{
			// TODO: LOG ERROR

			exit(-1);
		}
	}

	void Application::Shutdown()
	{
		try
		{
			delete(m_viewport);
			
			delete(m_batchRenderer);

			m_sceneManager->Shutdown();
			delete(m_sceneManager);

			m_imGuiManager->Shutdown();
			delete(m_imGuiManager);

			m_windowManager->Shutdown();
			delete(m_windowManager);

		}
		catch (std::exception e)
		{
			// TODO: LOG ERROR
		}
		
	}

	void Application::CreateApplication(const char* name)
	{
		if (!m_windowManager)
			throw std::exception("Window Manager is null!");

		m_windowManager->CreateWindow(name);

		if(!m_imGuiManager)
			throw std::exception("ImGui Manager is null!");

		m_imGuiManager->SetUpImGui(m_windowManager->GetWnd());

		if (!m_imGuiManager)
			throw std::exception("ImGui Manager is null!");

		if (!m_sceneManager)
			throw std::exception("Scene Manager is null!");

		if (!m_batchRenderer)
			throw std::exception("Renderer is null!");

		if (!m_viewport)
			throw std::exception("Viewport is null!");
	}

	void Application::Run()
	{
		bool createDockspace = true;

		// TODO: REMOVE JUST TESTING
		// Create Scene
		Scene* s = m_sceneManager->CreateScene("Test Scene");

		// Create Entity
		ECS::Entity e1("Cube");
		ECS::LoadSystem loadSystem;
		ECS::Model m = loadSystem.LoadModel("D:/Dev/Projects/QueenEngine/Assets/Models/cube.obj");
		e1.AddComponent<ECS::Model>(&m);

		ECS::Transform t;
		t.p_position = glm::vec3(1.0f, 1.0f, 1.0f);
		t.p_rotation = glm::vec3(1.0f, 1.0f, 1.0f);
		t.p_scale = glm::vec3(1.0f, 1.0f, 1.0f);
		e1.AddComponent<ECS::Transform>(&t);

		ECS::Entity e2("Cube 2");
		ECS::Model m2 = loadSystem.LoadModel("D:/Dev/Projects/QueenEngine/Assets/Models/Monkey.obj");
		e2.AddComponent<ECS::Model>(&m2);

		// Add Entity To Scene
		s->AddEntity(&e1);
		s->AddEntity(&e2);

		//std::printf("%s", s->Serialise().c_str());
		
		glm::mat4 model = glm::mat4(1.0f);

		// Load Scene Data to Renderer
		m_batchRenderer->LoadSceneVertexData(*s);
		m_batchRenderer->CreateBuffers();

		Renderer::Shader shader;
		shader.CreateProgram(
			"D:/Dev/Projects/QueenEngine/Assets/Shaders/vertex.vert",
			"D:/Dev/Projects/QueenEngine/Assets/Shaders/fragment.frag"
		);

		// Create FrameBuffer
		m_viewport->x = (float) m_windowManager->GetWidth();
		m_viewport->y = (float) m_windowManager->GetHeight();

		Renderer::FrameBuffer fbo;
		fbo.CreateFrameBuffer(m_viewport->x, m_viewport->y);

		while (!m_windowManager->ShouldWindowClose())
		{
			m_timer.Start();

			fbo.Bind();
			m_windowManager->EarlyUpdate();

			// Update Camera aspect ratio
			m_viewport->camera.SetSize(m_viewport->x, m_viewport->y);
			m_viewport->camera.CalculateViewMatrix();
			m_viewport->camera.CalculateProjectionMatrix();

			{
			shader.UseProgram();
			shader.SetUniformLocationMat4f("model", model);
			shader.SetUniformLocationMat4f("view", m_viewport->camera.GetViewMatrix());
			shader.SetUniformLocationMat4f("projection", m_viewport->camera.GetProjectionMatrix());
			
			// Here we draw
			m_batchRenderer->OnUpdate();

			// Unbind fbo, nothing more to render on texture
			fbo.Unbind();
			}

			// ImGUI New Frame
			m_imGuiManager->NewFrame();

			// Draw ImGUI Windows
			m_imGuiManager->CreateDockSpace(&createDockspace);
			m_imGuiManager->Benchmark(m_timer.p_durationInMs);
			m_imGuiManager->RenderStats(m_batchRenderer->GetRenderStats());
			m_imGuiManager->SceneData(*s);
			m_imGuiManager->ContentBrowserWnd();
			m_imGuiManager->ViewportDetails(m_viewport->camera);
			m_imGuiManager->Viewport(*m_viewport, fbo);

			m_imGuiManager->Render();
			m_imGuiManager->LateUpdate(m_windowManager->GetWnd());
			m_windowManager->LateUpdate();
			
			m_timer.Stop();
			m_timer.DurationInMs();
		}
	}
}
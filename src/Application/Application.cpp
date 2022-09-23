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
#include "../Scenes/Scene.h"
#include "../Utilities/ObjParser.h"

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

			// Renderer
			m_batchRenderer = new Renderer::BatchRenderer();
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
			m_imGuiManager->Shutdown();
			delete(m_imGuiManager);

			m_windowManager->Shutdown();
			delete(m_windowManager);

			delete(m_batchRenderer);
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
		
		bool createDockspace = true;
		m_imGuiManager->SetUpImGui(m_windowManager->GetWnd());
	}

	void Application::Run()
	{
		bool createDockspace = true;
		
		if (!m_windowManager)
			throw std::exception("Window Manager is null!");

		if (!m_imGuiManager)
			throw std::exception("ImGui Manager is null!");

		// TODO: REMOVE JUST TESTING

		Scene scene;

		ECS::Entity e1;
		ObjParser objParser;
		objParser.Parse("D:/Dev/Projects/QueenEngine/Assets/Models/Monkey.obj");
		ECS::Model m = {};
		m.p_name = objParser.GetObjData().name.c_str();
		m.p_vertices = objParser.GetObjData().vertices;
		m.p_indices = objParser.GetObjData().vertexIndices;
		e1.AddComponent<ECS::Model>(&m);

		ECS::Entity e2("Sphere");
		ObjParser objParser2;
		objParser2.Parse("D:/Dev/Projects/QueenEngine/Assets/Models/sphere.obj");
		ECS::Model m2 = {};
		m2.p_name = objParser2.GetObjData().name.c_str();
		m2.p_vertices = objParser2.GetObjData().vertices;
		m2.p_indices = objParser2.GetObjData().vertexIndices;
		e2.AddComponent<ECS::Model>(&m2);

		ECS::Entity e3("Pinye");
		ObjParser objParser3;
		objParser3.Parse("D:/Dev/Projects/QueenEngine/Assets/Models/cube.obj");
		ECS::Model m3 = {};
		m3.p_name = objParser3.GetObjData().name.c_str();
		m3.p_vertices = objParser3.GetObjData().vertices;
		m3.p_indices = objParser3.GetObjData().vertexIndices;
		e3.AddComponent<ECS::Model>(&m3);
		
		scene.AddEntity(&e1);
		scene.AddEntity(&e2);
		scene.AddEntity(&e3);
		
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));
	
		/*Renderer::VertexArrayObject vao;
		Renderer::VertexBuffer vbo;
		Renderer::ElementBuffer ebo;

		vao.GenerateBuffer();
		vbo.GenerateBuffer();
		ebo.GenerateBuffer();

		vao.BindBuffer();

		vbo.BindBuffer();
		vbo.BindData(e1.GetComponent<ECS::Model>()->p_vertices);

		ebo.BindBuffer();
		ebo.BindData(e1.GetComponent<ECS::Model>()->p_indices);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		vao.UnbindBuffer();*/

		m_batchRenderer->LoadSceneVertexData(scene);
		m_batchRenderer->CreateBuffers();

		Renderer::Shader shader;
		shader.CreateProgram(
			"D:/Dev/Projects/QueenEngine/Assets/Shaders/vertex.vert",
			"D:/Dev/Projects/QueenEngine/Assets/Shaders/fragment.frag"
		);

		// Create FrameBuffer
		m_viewport.x = (float) m_windowManager->GetWidth();
		m_viewport.y = (float) m_windowManager->GetHeight();
		Renderer::FrameBuffer fbo;
		fbo.CreateFrameBuffer(m_viewport.x, m_viewport.y);

		while (!m_windowManager->ShouldWindowClose())
		{
			fbo.Bind();

			m_timer.Start();
			m_windowManager->EarlyUpdate();

			// ImGUI New Frame
			m_imGuiManager->NewFrame();

			// Render Stuff
			glm::mat4 projection = glm::perspective(45.0f, m_viewport.x/m_viewport.y, 0.0f, 100.0f);

			shader.UseProgram();

			shader.SetUniformLocationMat4f("model", model);
			shader.SetUniformLocationMat4f("view", viewMatrix);
			shader.SetUniformLocationMat4f("projection", projection);

			/*vao.BindBuffer();
			glDrawElements(
				GL_TRIANGLES, 
				objParser.GetObjData().vertexIndices.size(), 
				GL_UNSIGNED_INT, 
				0
			);*/

			m_batchRenderer->OnUpdate();

			fbo.Unbind();

			// Draw ImGUI Windows
			m_imGuiManager->CreateDockSpace(&createDockspace);
			m_imGuiManager->Benchmark(m_timer.p_durationInMs);
			m_imGuiManager->RenderStats(m_batchRenderer->GetRenderStats());
			m_imGuiManager->Viewport(m_viewport, fbo);

			m_imGuiManager->Render();
			m_imGuiManager->LateUpdate(m_windowManager->GetWnd());
			m_windowManager->LateUpdate();
			
			m_timer.Stop();
			m_timer.DurationInMs();
		}
	}
}
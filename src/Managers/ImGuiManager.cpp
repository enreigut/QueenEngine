#include "ImGuiManager.h"

#include <exception>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

namespace Queen
{
	namespace Managers
	{
		ImGuiManager::ImGuiManager()
		{

		}

		ImGuiManager::~ImGuiManager()
		{

		}

		void ImGuiManager::Start()
		{
			if (IsRunning())
				throw std::exception("Manager already initialised!");

			SetRunning(true);
		}

		void ImGuiManager::Shutdown()
		{
			if (!IsRunning())
				throw std::exception("Manager is already shutted down!");

			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
			ImGui::DestroyContext();

			SetRunning(false);
		}

		void ImGuiManager::SetUpImGui(GLFWwindow* wnd)
		{
			IMGUI_CHECKVERSION();
			ImGui::CreateContext();

			ImGuiIO& io = ImGui::GetIO(); (void)io;
			io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
			io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
			io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

			ImGui::StyleColorsDark();

			ImGui_ImplGlfw_InitForOpenGL(wnd, true);
			ImGui_ImplOpenGL3_Init("#version 100");
		}

		void ImGuiManager::NewFrame()
		{
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
		}

		void ImGuiManager::Render()
		{
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		}

		void ImGuiManager::LateUpdate(GLFWwindow* wnd)
		{
			// Set Multiviewport
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				GLFWwindow* backup_current_context = wnd;
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();
				glfwMakeContextCurrent(backup_current_context);
			}
		}

		// Windows
		void ImGuiManager::CreateDockSpace(bool* p_open)
		{
			static bool opt_fullscreen = true;
			static bool opt_padding = false;
			static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

			ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

			// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
			// and handle the pass-thru hole, so we ask Begin() to not render a background.
			if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
				window_flags |= ImGuiWindowFlags_NoBackground;

			if (!opt_padding)
				ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

			ImGui::Begin("DockSpace", p_open, window_flags);

			if (!opt_padding)
				ImGui::PopStyleVar();

			if (opt_fullscreen)
				ImGui::PopStyleVar(2);

			// Submit the DockSpace
			ImGuiIO& io = ImGui::GetIO();
			if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
			{
				ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
				ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
			}

			ImGui::End();
		}

		void ImGuiManager::Benchmark(float& frameDurationInMs)
		{
			ImGui::Begin("Benchmark");

			ImGui::Text("%f ms", frameDurationInMs);
			ImGui::Text("%f FPS", 1/frameDurationInMs);

			ImGui::End();
		}

		void ImGuiManager::RenderStats(Renderer::RenderStats&& stats)
		{
			ImGui::Begin("Render Stats");

			ImGui::Text("%d Draw Calls", stats.drawCalls);
			ImGui::Text("%d Vertices", stats.vertices);
			ImGui::Text("%d Indices", stats.indices);

			ImGui::End();
		}

		void ImGuiManager::Viewport(Queen::Viewport& vp, Renderer::FrameBuffer& fbo)
		{
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
			
			ImGui::Begin("Viewport");
			
			ImVec2 vwSize = ImGui::GetContentRegionAvail();
			vp.x = vwSize.x;
			vp.y = vwSize.y;

			if (
				vwSize.x > 0.0f && 
				vwSize.y > 0.0f &&
				(vwSize.x != vp.x || vwSize.y != vp.y)
			)
			{
				vp.x = vwSize.x;
				vp.y = vwSize.y;

				printf("%f", vp.x);
				printf("%f", vp.y);

				glViewport(0, 0, (GLsizei)vp.x, (GLsizei)vp.y);
				fbo.CreateFrameBuffer(vp.x, vp.y);
			}
		
			ImGui::PopStyleVar();

			ImGui::Image((void*)fbo.GetColorAttachment(), { vp.x, vp.y });

			ImGui::End();
		}
	}
}
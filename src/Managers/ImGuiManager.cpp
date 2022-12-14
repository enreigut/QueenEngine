#include "ImGuiManager.h"

#include <exception>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

namespace Queen
{
	namespace Managers
	{
		static float w = 200.0f;
		static float h = 0.0f;

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

		void ImGuiManager::SceneData(Scene& scene)
		{
			ImGui::Begin("Scene Data");

			ImGui::Text("%s", scene.GetSceneName());
			ImGui::Separator();

			for(auto e: scene.GetEntities())
				ImGui::Text("%s", e.first);

			ImGui::End();
		}

		void ImGuiManager::ContentBrowserWnd()
		{
			ImGui::Begin("Content Browser");

			// Main Directory
			ImGui::Text("Main Directory: ");
			ImGui::SameLine();
			if (ImGui::Combo("##", &m_contentBrowser.p_count, m_contentBrowser.p_directories, IM_ARRAYSIZE(m_contentBrowser.p_directories), 2))
			{
				m_contentBrowser.p_currentPath = m_contentBrowser.p_directories[0];
			}

			// Show Current Directory
			ImGui::Text("Current Directory:");
			ImGui::SameLine();
			ImGui::Button(m_contentBrowser.p_currentPath.string().c_str());

			// Folders Child
			FolderAndFile ff = m_contentBrowser.GetDirectoryData();
			std::string path;
			
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
			ImGui::BeginChild("Folders", ImVec2(w, 0), true, 
				ImGuiWindowFlags_HorizontalScrollbar
			);
			
			if (std::filesystem::path(m_contentBrowser.p_directories[0]) != m_contentBrowser.p_currentPath)
			{
				if (ImGui::Button("/.."))
					m_contentBrowser.p_currentPath = m_contentBrowser.p_currentPath.parent_path();
			}
			for (auto folder : ff.p_folders)
			{
				path = folder.path().string();
				if (ImGui::Button(path.c_str()))
				{
					m_contentBrowser.p_currentPath /= folder.path().filename();
				}
			}
			ImGui::EndChild();
			
			ImGui::SameLine();

			h = ImGui::GetContentRegionAvail().y;
			ImGui::InvisibleButton("vsplitter", ImVec2(5.0f, h));
			
			if (ImGui::IsItemHovered())
			{
				ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);
			}
			
			if (ImGui::IsItemActive())
			{
				ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);
				w += ImGui::GetIO().MouseDelta.x;
			}

			ImGui::SameLine();

			ImGui::BeginChild("Files", ImVec2(0, 0), true);
			
			for (auto file : ff.p_files)
			{
				path = file.path().string();
				ImGui::Text("%s", path.c_str());
			}
			ImGui::EndChild();
			ImGui::PopStyleVar();
			
			ImGui::End();
		}

		void ImGuiManager::ViewportDetails(Camera& camera)
		{
			ImGui::Begin("Viewport Details");

			ImGui::Text("Camera Properties");
			
			ImGui::Separator();
			ImGui::DragFloat("X pos", &camera.p_position.x, 0.1f);
			ImGui::DragFloat("Y pos", &camera.p_position.y, 0.1f);
			ImGui::DragFloat("Z pos", &camera.p_position.z, 0.1f);
			ImGui::Separator();

			ImGui::DragFloat("Yaw", &camera.m_yaw, 0.1f);
			ImGui::DragFloat("Pitch", &camera.m_pitch, 0.1f, -89.0f, 89.0f);
			ImGui::DragFloat("Roll", &camera.m_roll, 0.1f);
			ImGui::Separator();

			ImGui::SliderFloat("FOV", &camera.p_fov, 1.0f, 90.0f);
			ImGui::Text("%f Width", camera.GetWidth());
			ImGui::Text("%f Height", camera.GetHeight());

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
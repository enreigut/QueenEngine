#pragma once

#include <IMGUI/imgui.h>
#include <IMGUI/imgui_impl_glfw.h>
#include <IMGUI/imgui_impl_opengl3.h>

#include "Manager.h"
#include "../Renderer/FrameBuffer.h"

namespace Queen
{
	namespace Managers
	{
		// TODO: Separate to specifications of app
		struct Viewport
		{
			float width;
			float height;
		};

		class ImGuiManager : public Manager
		{
		public:
			ImGuiManager();
			~ImGuiManager();

			// Getters
			float GetViewportWidth() const { return m_viewportWidth; }
			float GetViewportHeight() const { return m_viewportHeight; }

			// Setters

			// Derived
			void Start() override;
			void Shutdown() override;
			void SetUpImGui(GLFWwindow* wnd);
			void NewFrame();
			void Render();
			void LateUpdate(GLFWwindow* wnd);

			// Windows
			void CreateDockSpace(bool* p_open);
			void Benchmark(float& frameDurationInMs);
			void Viewport(Viewport& vp, Renderer::FrameBuffer& fbo);

		private:
			float m_viewportWidth = 0.0f;
			float m_viewportHeight = 0.0f;
		};
	}
}
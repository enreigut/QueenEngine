#pragma once

#include <IMGUI/imgui.h>
#include <IMGUI/imgui_impl_glfw.h>
#include <IMGUI/imgui_impl_opengl3.h>

#include "Manager.h"
#include "../Renderer/FrameBuffer.h"
#include "../Renderer/Viewport.h"

namespace Queen
{
	namespace Managers
	{
		class ImGuiManager : public Manager
		{
		public:
			ImGuiManager();
			~ImGuiManager();

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

		};
	}
}
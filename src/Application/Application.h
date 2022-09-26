#pragma once

// Managers
#include "../Managers/ImGuiManager.h"
#include "../Managers/WindowManager.h"
#include "../Managers/SceneManager.h"

// Renderer
#include "../Renderer/BatchRenderer.h"
#include "../Renderer/Viewport.h"

// Utils
#include "../Utilities/Timer.h"

namespace Queen
{
	class Application
	{
	public:
		Application();
		~Application();

		// Getters

		// Setters

		// Derived
		void StartManagers();
		void Shutdown();
		void CreateApplication(const char* name = "Test Application");
		void Run();

	private:
		Timer m_timer;
		
		// Managers
		Managers::WindowManager* m_windowManager = nullptr;
		Managers::ImGuiManager* m_imGuiManager = nullptr;
		Managers::SceneManager* m_sceneManager = nullptr;

		// Renderer
		Renderer::BatchRenderer* m_batchRenderer = nullptr;
		Viewport* m_viewport = nullptr;
	};
}
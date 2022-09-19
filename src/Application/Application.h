#pragma once

// Managers
#include "../Managers/WindowManager.h"

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
		Managers::WindowManager* m_windowManager = nullptr;
	};
}
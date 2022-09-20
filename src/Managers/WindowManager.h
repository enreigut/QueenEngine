#pragma once

#include "Manager.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Queen
{
	namespace Managers
	{
		/*
		This manager handles everything realated to the window:
			- Inititalise GLFW and GLEW
			- GLFW API
			- Window Creation
			- Window Callbacks
		*/
		class WindowManager: public Manager
		{
		public:
			WindowManager();
			~WindowManager();

			// Getter
			inline GLFWwindow* GetWnd() const { return m_window; }
			inline int GetWidth() const { return m_width; }
			inline int GetHeight() const { return m_height; }
			inline float GetAspectRatio() const { return m_aspectRatio; }

			// Setter
			inline void SetWidth(int& width) { m_width = width; }
			inline void SetHeight(int& height) { m_height = height; }
			inline void SetAspectRatio(float aspectRatio) { m_aspectRatio = aspectRatio; }

			// Derived
			void Start() override;
			void Shutdown() override;
			void CreateWindow(const char* name);
			bool ShouldWindowClose();
			void EarlyUpdate();
			void LateUpdate();

		private:
			GLFWwindow* m_window = nullptr;
			int m_width = 1280;
			int m_height = 720;
			float m_aspectRatio = 1.0f;
		};
	}
}
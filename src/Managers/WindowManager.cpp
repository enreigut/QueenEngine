#include "WindowManager.h"

#include <exception>

namespace Queen
{
	namespace Managers
	{
		WindowManager* wndManager = nullptr;
		
		// Callbacks
		void Window_size_callback(GLFWwindow* window, int width, int height)
		{
			// TODO: Fix when editor is not used
			/*wndManager->SetWidth(width);
			wndManager->SetHeight(height);
			wndManager->SetAspectRatio((float) wndManager->GetWidth() / (float) wndManager->GetHeight());
			glViewport(0, 0, wndManager->GetWidth(), wndManager->GetHeight());*/
		}

		WindowManager::WindowManager()
		{
			if (wndManager == nullptr)
				wndManager = this;
		}

		WindowManager::~WindowManager()
		{

		}

		void WindowManager::Start()
		{
			if (IsRunning())
				throw std::exception("Manager already initialised!");
			
			SetRunning(true);
		}

		void WindowManager::Shutdown()
		{
			if (!IsRunning())
				throw std::exception("Manager is already shutted down!");

			/* GLFW Clean Up */
			glfwDestroyWindow(m_window);
			glfwTerminate();

			SetRunning(false);
		}

		void WindowManager::CreateWindow(const char* name)
		{
			if (!IsRunning())
				throw std::exception("Manager needs to be started!");

			// Initialise GLFW
			if(!glfwInit())
				throw std::exception("Error initialising GLFW!");

			// Set up some config
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
			// glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);

			// Create window and check that it has been created correctly
			m_window = glfwCreateWindow(m_width, m_height, name, nullptr, nullptr);
			if(!m_window)
				throw std::exception("Error creating GLFWWindow!");
			
			// Calculate Ratio for GL perspective
			m_aspectRatio = (float)m_width / (float)m_height;

			// Set window as current context
			glfwMakeContextCurrent(m_window);

			// Set Up Callbacks
			glfwSetWindowSizeCallback(m_window, Window_size_callback);
			
			// Disable V-Sync (If enabled, fps limited to Screen refresh rate)
			glfwSwapInterval(0);

			// Initialise GLEW
			GLenum glew = glewInit();
			if(glew != GLEW_OK)
				throw std::exception("Error initialising GLEW!");
		}

		bool WindowManager::ShouldWindowClose()
		{
			if(!IsRunning())
				throw std::exception("Manager needs to be started!");

			if(!m_window)
				throw std::exception("No defined window!");

			return glfwWindowShouldClose(m_window);
		}

		void WindowManager::EarlyUpdate()
		{
			glClearColor(0.25f, 0.45f, 0.45f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
		}

		void WindowManager::LateUpdate()
		{
			glfwPollEvents();
			glfwSwapBuffers(m_window);
		}
	}
}
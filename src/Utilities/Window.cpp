#include "Window.h"

Window::Window()
{

}

Window::~Window()
{

}

bool Window::CreateWindow(const char* name, int& width, int& height)
{
	m_logger.Log(LogLevel::INFO, "Creating Window...");

	m_window = glfwCreateWindow(width, height, name, nullptr, nullptr);

	if (!m_window)
		return false;

	glfwMakeContextCurrent(m_window);
	glfwSwapInterval(0);

	m_imGui.SetUp(m_window);

	m_logger.Log(LogLevel::SUCCESS, "Window created succesfully!");
	return true;
}

bool Window::ShouldClose()
{
	return glfwWindowShouldClose(m_window);
}

void Window::StartUpdate()
{
	glViewport(0, 0, m_width, m_height);
	glClearColor(0.25f, 0.45f, 0.45f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	m_imGui.NewFrame();
	m_imGui.CreateDockSpace(&m_imGui.p_createDockspace);
}

void Window::LateUpdate()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}

	glfwPollEvents();
	glfwSwapBuffers(m_window);
}

void Window::Clean()
{
	m_imGui.Clean();

	glfwDestroyWindow(m_window);
	glfwTerminate();
}
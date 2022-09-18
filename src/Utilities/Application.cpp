#include "Application.h"

Application::Application()
{

}

Application::~Application() 
{

}

void Application::CreateApplication(const char* name, int width, int height)
{
	m_logger.Log(LogLevel::INFO, "Creating Application...");

	InitGLFW();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);

	m_window.CreateWindow(name, width, height);

	InitGLEW();

	m_logger.Log(LogLevel::SUCCESS, "Application created successfully!");
}

bool Application::IsRunning()
{
	return !m_window.ShouldClose();
}

void Application::StartUpdate()
{
	m_timer.Start();
	m_window.StartUpdate();
}

void Application::LateUpdate()
{
	m_window.LateUpdate();
	m_timer.Stop();
	m_timer.DurationInMs();
}

void Application::Clean()
{
	m_window.Clean();
}

void Application::InitGLFW()
{
	if (!glfwInit())
		throw std::exception("Unable to initialise GLFW library!");

	m_logger.Log(LogLevel::SUCCESS, "GLFW initialised succesfully!");
}

void Application::InitGLEW()
{
	GLenum error = glewInit();
	if (error != GLEW_OK)
		throw std::exception("Unable to initialise GLEW library!");

	m_logger.Log(LogLevel::SUCCESS, "GLEW initialised succesfully!");
}
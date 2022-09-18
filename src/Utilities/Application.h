#pragma once

#include "Window.h"

class Application
{
public:
	Application();
	~Application();

	// Getters
	float GetFrameDuration() const { return m_timer.p_durationInMs; }

	// Setters
	void CreateApplication(const char* name = "Test Application", int width = 1280, int height = 720);
	bool IsRunning();
	void StartUpdate();
	void LateUpdate();
	void Clean();

private:
	void InitGLFW();
	void InitGLEW();

private:
	Logger m_logger;
	Window m_window;
	Timer m_timer;
};
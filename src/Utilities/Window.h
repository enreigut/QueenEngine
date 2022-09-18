#pragma once

#include "ImGuiApi.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Logger.h"

class Window
{
public:
	Window();
	~Window();

	// Getters

	// Setters

	// Derived
	bool CreateWindow(const char* name, int& width, int& height);
	bool ShouldClose();
	void StartUpdate();
	void LateUpdate();
	void Clean();

private:
	GLFWwindow* m_window = nullptr;
	int m_width = 1280;
	int m_height = 720;
	ImGuiApi m_imGui;
	Logger m_logger;
};

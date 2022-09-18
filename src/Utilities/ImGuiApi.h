#pragma once

#include <IMGUI/imgui.h>
#include <IMGUI/imgui_impl_glfw.h>
#include <IMGUI/imgui_impl_opengl3.h>

class ImGuiApi
{
public:
	ImGuiApi();
	~ImGuiApi();

	// Getters

	// Setters

	// Derived
	void SetUp(GLFWwindow* wnd);
	void NewFrame();
	void Clean();
	void CreateDockSpace(bool* p_open);

public:
	bool p_createDockspace = true;

private:

};

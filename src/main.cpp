#include <iostream>
#include "Utilities/Application.h"

void BenchmarkWindow(Application& app)
{
	float ms = app.GetFrameDuration();

	ImGui::Begin("Benchmarking");

	ImGui::Text("%f ms", ms);
	ImGui::Text("%f FPS", 1 / ms);

	ImGui::End();
}


int main()
{
	static Application app;
	app.CreateApplication();

	while (app.IsRunning())
	{
		app.StartUpdate();

		BenchmarkWindow(app);

		app.LateUpdate();
	}

	app.Clean();

	return 0;
}
#include <iostream>
#include "Application/Application.h"

int main()
{
	static Queen::Application queenEgine;
	queenEgine.StartManagers();
	queenEgine.CreateApplication();
	queenEgine.Run();
	queenEgine.Shutdown();

	return 0;
}
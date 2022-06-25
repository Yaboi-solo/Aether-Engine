#pragma once

#include <Core/Application.h>

extern Aether::Application* Aether::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Aether::CreateApplication();
	app->Run();
	delete app;
}
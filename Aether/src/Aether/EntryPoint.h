#pragma once

#ifdef AT_PLATFORM_WINDOWS

extern Aether::Application* Aether::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Aether::CreateApplication();
	app->Run();
	delete app;
}

#endif

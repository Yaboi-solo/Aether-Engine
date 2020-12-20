#pragma once

#ifdef AT_PLATFORM_WINDOWS

extern Aether::Application* Aether::CreateApplication();

int main(int argc, char** argv)
{
	Aether::Log::Init();
	AT_CORE_WARN("Initialized Log!");
	int a = 5;
	AT_INFO("Hello! Var={0}", a);

	auto app = Aether::CreateApplication();
	app->Run();
	delete app;
}

#endif

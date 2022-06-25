#define AT_ENTRY
#include <Aether.h>

class SandboxLayer : public Aether::Layer
{
	virtual void OnAttach() override
	{
		//AT_FATAL("Hello, {0}!", "World");
		//AT_ERROR("Hello, {0}!", "World");
		//AT_WARN("Hello, {0}!", "World");
		//AT_INFO("Hello, {0}!", "World");
		//AT_TRACE("Hello, {0}!", "World");
	}

	virtual void OnDetach() override
	{

	}

	virtual void OnUpdate() override
	{

	}
};

class Sandbox : public Aether::Application
{
public:
	Sandbox()
		: Application("Sandbox")
	{

		PushLayer(new SandboxLayer());
	}

	~Sandbox()
	{
	}
};

Aether::Application* Aether::CreateApplication()
{
	return new Sandbox();
}
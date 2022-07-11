#define AT_ENTRY
#include <Aether.h>

class SandboxLayer : public Aether::Layer
{
public:
	virtual void OnAttach() override
	{
		//AT_FATAL("Hello, {0}!", "World");
		//AT_ERROR("Hello, {0}!", "World");
		//AT_WARN("Hello, {0}!", "World");
		//AT_INFO("Hello, {0}!", "World");
		//AT_TRACE("Hello, {0}!", "World");
		renderer.Init();
	}

	virtual void OnDetach() override
	{
		renderer.Shutdown();
	}

	virtual void OnUpdate() override
	{
		renderer.DrawQuad(Aether::Matrix4f::Identity(), Aether::Vector4f(1.0f));
	}

private:
	Aether::Renderer2D renderer;
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
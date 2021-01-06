#include <Aether.h>

class ExampleLayer : public Aether::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		 //Logs EVERY update, not recommended
		 //AT_INFO("ExampleLayer::Update");
	}

	void OnEvent(Aether::Event& event) override
	{
		//Logs every event, also not recommended
		//AT_TRACE("{0}", event);
	}
};

class Sandbox : public Aether::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Aether::ImGuiLayer());
	}
	~Sandbox()
	{

	}

};

Aether::Application* Aether::CreateApplication()
{
	return new Sandbox();
}
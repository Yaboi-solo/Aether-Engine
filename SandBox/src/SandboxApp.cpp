#include <Aether.h>

#include "imgui/imgui.h"

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

		//if (Aether::Input::IsKeyPressed(AT_KEY_TAB))
		//	AT_TRACE("Tab key is pressed!");
	}

	virtual void OnImGuiRender() override 
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
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
	}
	
	~Sandbox()
	{

	}

};

Aether::Application* Aether::CreateApplication()
{
	return new Sandbox();
}
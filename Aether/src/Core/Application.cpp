#include "atpch.h"
#include "Application.h"

#include "Event/ApplicationEvent.h"

namespace Aether {

	Application* Application::s_Instance = nullptr;

	Application::Application(const std::string& name)
		: m_Name(name)
	{
		AT_ASSERT(!s_Instance, "Application instance already exists!");
		s_Instance = this;

		AT_WARN("Initializing Aether...");

		m_Window = Window::Create(WindowProperties(name));

		//// Set callbacks
		EventManager::On<WindowCloseEvent>([this](const Event& e)
			{
				m_Running = false;
			});
		EventManager::On<WindowResizeEvent>([this](const Event& e)
			{
				//WindowResizeEvent event = (const WindowResizeEvent&)e;
			});


		m_Running = true;
	}

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::Close()
	{
		m_Running = false;
	}

	void Application::Run()
	{
		while (m_Running)
		{

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_Window->Update();
		}
	}
}
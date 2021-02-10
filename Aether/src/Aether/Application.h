#pragma once

#include "Core.h"

#include "Window.h"
#include "Aether/LayerStack.h"
#include "Aether/Events/Event.h"
#include "Aether/Events/ApplicationEvent.h"

#include "Aether/ImGui/ImGuiLayer.h"

namespace Aether {
	
	class AETHER_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClosed(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
	private:
		static Application* s_Instance;
	};

	//To be defined in client
	Application* CreateApplication();


}

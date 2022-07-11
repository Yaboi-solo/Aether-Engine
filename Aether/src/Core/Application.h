#pragma once

int main(int argc, char** argv);

#include "Window.h"
#include "LayerStack.h"

namespace Aether {

	class Application
	{
	public:
		Application(const std::string& name);
		~Application();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		void Close();

		static Application& Get() { return *s_Instance; }

		const std::string& GetName() { return m_Name; }


		Window& GetWindow() { return *m_Window; }

	private:
		void Run();
	private:
		std::string m_Name;
		bool m_Running;
		bool m_Minimized;

		Scope<Window> m_Window;

		LayerStack m_LayerStack;
	private:
		static Application* s_Instance;
		friend int ::main(int argc, char** argv);
	};

	Application* CreateApplication();
}
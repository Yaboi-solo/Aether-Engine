#pragma once

#include "Core.h"

namespace Aether {
	
	class AETHER_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	//To be defined in client
	Application* CreateApplication();


}

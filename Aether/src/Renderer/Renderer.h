#pragma once

#include "GraphicsContext.h"

#include "Core/Application.h"

namespace Aether {
	class Renderer
	{
	public:
		static Ref<GraphicsContext> GetContext()
		{
			return Application::Get().GetWindow().GetGraphicsContext();
		}

		static void Init();
		static void Shutdown();
	};
}
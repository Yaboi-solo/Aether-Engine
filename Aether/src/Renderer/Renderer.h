#pragma once

#include "GraphicsContext.h"

#include "Core/Application.h"

#include "RendererAPI.h"

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

		static void BeginFrame();
		static void EndFrame();

		static void Resize(uint32_t width, uint32_t height);
	private:
		static Ref<RendererAPI> m_API;
	};
}
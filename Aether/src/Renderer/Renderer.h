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

		static void Init()
		{
			m_API = RendererAPI::Create();
			m_API->Init();
		}

		static void Shutdown()
		{
			m_API->Shutdown();
		}

		static void BeginFrame()
		{
			m_API->BeginFrame();
		}

		static void EndFrame()
		{
			m_API->EndFrame();
		}

		static void Resize(uint32_t width, uint32_t height)
		{
			m_API->Resize(width, height);
		}

		static void DrawIndexed(const Ref<IndexBuffer>& indexBuffer)
		{
			m_API->DrawIndexed(indexBuffer);
		}
		
	private:
		static Ref<RendererAPI> m_API;
	};
}
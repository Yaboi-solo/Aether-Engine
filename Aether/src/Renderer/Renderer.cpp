#include "atpch.h"
#include "Renderer.h"

namespace Aether {
	
	Ref<RendererAPI> Renderer::m_API;

	void Renderer::Init()
	{
		m_API = RendererAPI::Create();
		m_API->Init();
	}

	void Renderer::Shutdown()
	{
		m_API->Shutdown();
	}
	
	void Renderer::BeginFrame()
	{
		m_API->BeginFrame();
	}
	
	void Renderer::EndFrame()
	{
		m_API->EndFrame();
	}
	void Renderer::Resize(uint32_t width, uint32_t height)
	{
		m_API->Resize(width, height);
	}
}
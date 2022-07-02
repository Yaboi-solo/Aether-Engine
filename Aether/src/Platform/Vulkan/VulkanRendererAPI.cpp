#include "atpch.h"
#include "VulkanRendererAPI.h"


namespace Aether {
	void VulkanRendererAPI::Init()
	{
		 m_Context = VulkanContext::Get();
	}
	
	void VulkanRendererAPI::Shutdown()
	{
	}
	
	void VulkanRendererAPI::BeginFrame()
	{
		m_Context->GetSwapchain().BeginFrame();
	}
	
	void VulkanRendererAPI::EndFrame()
	{
		m_Context->GetSwapchain().Present();
	}
	
	void VulkanRendererAPI::Resize(uint32_t width, uint32_t height)
	{
		m_Context->Resize(width, height);
	}
}
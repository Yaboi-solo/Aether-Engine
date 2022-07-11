#pragma once

#include "Renderer/GraphicsContext.h"

#include "Vulkan.h"
#include "VulkanDevice.h"
#include "VulkanSwapchain.h"

#include "Renderer/Renderer.h"

namespace Aether {
	class VulkanContext : public GraphicsContext
	{
	public:
		VulkanContext(void* window, uint32_t width, uint32_t height);
		virtual ~VulkanContext() override;

		virtual void Init() override;

		Ref<VulkanDevice> GetDevice() { return m_Device; }
		VulkanSwapchain* GetSwapchain() { return &m_Swapchain; }
		
		const VkCommandPool& GetTransferCommandPool() const { return m_TransferCommandPool; }

		static VkInstance GetInstance() { return s_VulkanInstance; }
		static Ref<VulkanContext> Get() { return std::dynamic_pointer_cast<VulkanContext, GraphicsContext>(Renderer::GetContext()); }

		void Resize(uint32_t width, uint32_t height);
	private:
		void* m_Window;
		uint32_t m_WindowWidth, m_WindowHeight;

		inline static VkInstance s_VulkanInstance = nullptr;
		VkDebugReportCallbackEXT m_DebugReportCallback = nullptr;

		Ref<VulkanPhysicalDevice> m_PhysicalDevice;
		Ref<VulkanDevice> m_Device;

		VulkanSwapchain m_Swapchain;

		VkCommandPool m_TransferCommandPool;
	};
}
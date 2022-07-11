#pragma once

#include "Vulkan.h"
#include "VulkanDevice.h"

namespace Aether {
	
	class VulkanSwapchain
	{
	public:
		VulkanSwapchain() = default;
		
		void Init(VkInstance instance, Ref<VulkanDevice> device);
		void CreateSurface(void* windowHandle);
		void DestroySurface();
		void Create(uint32_t width, uint32_t height, bool vsync = false);
		void Recreate(uint32_t width, uint32_t height, bool vsync = false);
		void Destroy();

		void Resize(uint32_t width, uint32_t height);

		void BeginFrame();
		void Present();

		const VkRenderPass& GetRenderpass() const { return m_RenderPass; }

		VkCommandBuffer& GetCurrentCommandBuffer();

		uint32_t GetWidth() const { return m_Width; }
		uint32_t GetHeight() const { return m_Height; }
	private:
		VkInstance m_Instance = VK_NULL_HANDLE;
		Ref<VulkanDevice> m_Device;
		bool m_VSync = false;

		uint32_t m_Width, m_Height;
		
		VkSurfaceKHR m_Surface = VK_NULL_HANDLE;

		VkFormat m_ColorFormat;
		VkColorSpaceKHR m_ColorSpace;

		VkSwapchainKHR m_Swapchain = VK_NULL_HANDLE;
		uint32_t m_ImageCount = 0;
		std::vector<VkImage> m_VulkanImages;

		struct SwapchainImage
		{
			VkImage Image = VK_NULL_HANDLE;
			VkImageView ImageView = VK_NULL_HANDLE;
		};
		std::vector<SwapchainImage> m_Images;

		VkCommandPool m_CommandPool = VK_NULL_HANDLE;
		VkCommandBuffer m_CommandBuffer = VK_NULL_HANDLE;

		QueueFamilyIndices m_QueueFamilyIndices;

		struct {
			VkSemaphore ImageAvailable = VK_NULL_HANDLE;
			VkSemaphore RenderComplete = VK_NULL_HANDLE;
			VkFence InFlightFence = VK_NULL_HANDLE;
		} m_SyncObjects;

		std::vector<VkFramebuffer> m_Framebuffers;

		VkRenderPass m_RenderPass = VK_NULL_HANDLE;
	};
}
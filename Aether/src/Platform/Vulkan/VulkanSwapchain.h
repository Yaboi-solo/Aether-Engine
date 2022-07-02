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
		void Create(uint32_t width, uint32_t height, bool vsync = false);
		void Destroy();

		void Resize(uint32_t width, uint32_t height);

		void BeginFrame();
		void Present();
	private:
		VkInstance m_Instance = nullptr;
		Ref<VulkanDevice> m_Device;
		bool m_VSync = false;

		uint32_t m_Width, m_Height;
		
		VkSurfaceKHR m_Surface;

		VkFormat m_ColorFormat;
		VkColorSpaceKHR m_ColorSpace;

		VkSwapchainKHR m_Swapchain = nullptr;
		uint32_t m_ImageCount = 0;
		std::vector<VkImage> m_VulkanImages;

		struct SwapchainImage
		{
			VkImage Image = nullptr;
			VkImageView ImageView = nullptr;
		};
		std::vector<SwapchainImage> m_Images;

		VkCommandPool m_CommandPool;
		VkCommandBuffer m_CommandBuffer;

		QueueFamilyIndices m_QueueFamilyIndices;

		struct {
			VkSemaphore ImageAvailable;
			VkSemaphore RenderComplete;
			VkFence InFlightFence;
		} m_SyncObjects;

		uint32_t m_CurrentImageIndex;

		std::vector<VkFramebuffer> m_Framebuffers;

		VkRenderPass m_RenderPass = nullptr;
	};
}
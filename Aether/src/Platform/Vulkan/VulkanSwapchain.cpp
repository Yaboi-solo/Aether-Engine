#include "atpch.h"
#include "VulkanSwapchain.h"

#ifdef AT_PLATFORM_WINDOWS
#include <Windows.h>
#include <vulkan/vulkan_win32.h>
#endif

namespace Aether {
	void VulkanSwapchain::Init(VkInstance instance, Ref<VulkanDevice> device)
	{
		m_Instance = instance;
		m_Device = device;
	}
	
	void VulkanSwapchain::Create(uint32_t width, uint32_t height, bool vsync)
	{
		m_VSync = vsync;
		
		VkPhysicalDevice physicalDevice = m_Device->GetPhysicalDevice()->GetVulkanPhysicalDevice();
		VkDevice device = m_Device->GetVulkanDevice();
		
		VkSurfaceCapabilitiesKHR surfaceCapabilities;
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, m_Surface, &surfaceCapabilities);
		
		uint32_t presentModeCount;
		vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, m_Surface, &presentModeCount, nullptr);
		AT_ASSERT(presentModeCount > 0, "");
				
		std::vector<VkPresentModeKHR> presentModes(presentModeCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, m_Surface, &presentModeCount, presentModes.data());
		
		VkExtent2D swapchainExtent = {};
				
		if (surfaceCapabilities.currentExtent.width == (uint32_t)-1)
		{
			swapchainExtent.width = width;
			swapchainExtent.height = height;
		}
		else
		{
			swapchainExtent = surfaceCapabilities.currentExtent;
			width = surfaceCapabilities.currentExtent.width;
			height = surfaceCapabilities.currentExtent.height;
		}
		
		m_Width = width;
		m_Height = height;

		VkPresentModeKHR swapchainPresentMode = VK_PRESENT_MODE_FIFO_KHR;
		if (!m_VSync)
		{
			for (size_t i = 0; i < presentModeCount; i++)
			{
				if (presentModes[i] == VK_PRESENT_MODE_MAILBOX_KHR)
				{
					swapchainPresentMode = VK_PRESENT_MODE_MAILBOX_KHR;
					break;
				}
				if ((swapchainPresentMode != VK_PRESENT_MODE_MAILBOX_KHR) && (presentModes[i] == VK_PRESENT_MODE_IMMEDIATE_KHR))
				{
					swapchainPresentMode = VK_PRESENT_MODE_IMMEDIATE_KHR;
				}
			}
		}
		
		uint32_t desiredNumberOfSwapchainImages = surfaceCapabilities.minImageCount + 1;
		if (surfaceCapabilities.maxImageCount > 0 && desiredNumberOfSwapchainImages > surfaceCapabilities.maxImageCount)
		{
			desiredNumberOfSwapchainImages = surfaceCapabilities.maxImageCount;
		}
		
		VkSurfaceTransformFlagsKHR preTransform;
		if (surfaceCapabilities.supportedTransforms & VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR)
		{
			preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
		}
		else
		{
			preTransform = surfaceCapabilities.currentTransform;
		}
		
		VkCompositeAlphaFlagBitsKHR compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
				
		std::vector<VkCompositeAlphaFlagBitsKHR> compositeAlphaFlags = {
			VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
			VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR,
			VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR,
			VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR
		};
				
		for (auto& compositeAlphaFlag : compositeAlphaFlags)
		{
			if (surfaceCapabilities.supportedCompositeAlpha & compositeAlphaFlag)
			{
				compositeAlpha = compositeAlphaFlag;
				break;
			}
		}
		
		
		uint32_t formatCount;
		vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, m_Surface, &formatCount, nullptr);
		AT_ASSERT(formatCount > 0, "");
				
		std::vector<VkSurfaceFormatKHR> surfaceFormats(formatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, m_Surface, &formatCount, surfaceFormats.data());
		
		// Meaning all formats are available
		if ((formatCount == 1) && (surfaceFormats[0].format = VK_FORMAT_UNDEFINED))
		{
			m_ColorFormat = VK_FORMAT_B8G8R8A8_UNORM;
			m_ColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
		}
		else {
			bool found = false;
			for (auto&& surfaceFormat : surfaceFormats)
			{
				if (surfaceFormat.format == VK_FORMAT_B8G8R8A8_UNORM)
				{
					m_ColorFormat = VK_FORMAT_B8G8R8A8_UNORM;
					m_ColorSpace = surfaceFormat.colorSpace;
					found = true;
					break;
				}
			}
		
			if (!found)
			{
				m_ColorFormat = surfaceFormats[0].format;
				m_ColorSpace = surfaceFormats[0].colorSpace;
			}
		}


		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////

		VkSwapchainCreateInfoKHR swapchainCreateInfo = {};
		swapchainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		swapchainCreateInfo.surface = m_Surface;
		swapchainCreateInfo.imageArrayLayers = 1;
		swapchainCreateInfo.minImageCount = desiredNumberOfSwapchainImages;
		swapchainCreateInfo.imageFormat = m_ColorFormat;
		swapchainCreateInfo.imageColorSpace = m_ColorSpace;
		swapchainCreateInfo.imageExtent = swapchainExtent;
		swapchainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
		swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		swapchainCreateInfo.queueFamilyIndexCount = 0;
		swapchainCreateInfo.pQueueFamilyIndices = nullptr;
		swapchainCreateInfo.preTransform = (VkSurfaceTransformFlagBitsKHR)preTransform;
		swapchainCreateInfo.compositeAlpha = compositeAlpha;
		swapchainCreateInfo.presentMode = swapchainPresentMode;
		swapchainCreateInfo.clipped = VK_TRUE;
		swapchainCreateInfo.oldSwapchain = VK_NULL_HANDLE;
		
		if (m_Swapchain == VK_NULL_HANDLE)
			VK_CHECK_RESULT(vkCreateSwapchainKHR(device, &swapchainCreateInfo, nullptr, &m_Swapchain));

		if (m_Images.empty())
		{
			VK_CHECK_RESULT(vkGetSwapchainImagesKHR(device, m_Swapchain, &m_ImageCount, nullptr));
			m_Images.resize(m_ImageCount);
			m_VulkanImages.resize(m_ImageCount);
			VK_CHECK_RESULT(vkGetSwapchainImagesKHR(device, m_Swapchain, &m_ImageCount, m_VulkanImages.data()));

			for (uint32_t i = 0; i < m_ImageCount; i++)
			{
				VkImageViewCreateInfo imageViewInfo = {};
				imageViewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
				imageViewInfo.format = m_ColorFormat;
				imageViewInfo.image = m_VulkanImages[i];
				imageViewInfo.components = {
					VK_COMPONENT_SWIZZLE_R,
					VK_COMPONENT_SWIZZLE_G,
					VK_COMPONENT_SWIZZLE_B,
					VK_COMPONENT_SWIZZLE_A
				};
				imageViewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
				imageViewInfo.subresourceRange.baseMipLevel = 0;
				imageViewInfo.subresourceRange.levelCount = 1;
				imageViewInfo.subresourceRange.baseArrayLayer = 0;
				imageViewInfo.subresourceRange.layerCount = 1;
				imageViewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;

				m_Images[i].Image = m_VulkanImages[i];

				VK_CHECK_RESULT(vkCreateImageView(device, &imageViewInfo, nullptr, &m_Images[i].ImageView));
			}
		}

		m_QueueFamilyIndices = GetQueueFamilyIndices(physicalDevice);

		VkCommandPoolCreateInfo commandPoolCreateInfo = {};
		commandPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		commandPoolCreateInfo.queueFamilyIndex = m_QueueFamilyIndices.Graphics;
		commandPoolCreateInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
		if (m_CommandPool == VK_NULL_HANDLE)
			VK_CHECK_RESULT(vkCreateCommandPool(device, &commandPoolCreateInfo, nullptr, &m_CommandPool));

		VkCommandBufferAllocateInfo commandBufferAllocateInfo = {};
		commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		commandBufferAllocateInfo.commandPool = m_CommandPool;
		commandBufferAllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		commandBufferAllocateInfo.commandBufferCount = 1;
		VK_CHECK_RESULT(vkAllocateCommandBuffers(device, &commandBufferAllocateInfo, &m_CommandBuffer));

		VkSemaphoreCreateInfo semaphoreCreateInfo = {};
		semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
		if (m_SyncObjects.ImageAvailable == VK_NULL_HANDLE)
			VK_CHECK_RESULT(vkCreateSemaphore(device, &semaphoreCreateInfo, nullptr, &m_SyncObjects.ImageAvailable));
		if (m_SyncObjects.RenderComplete == VK_NULL_HANDLE)
			VK_CHECK_RESULT(vkCreateSemaphore(device, &semaphoreCreateInfo, nullptr, &m_SyncObjects.RenderComplete));

		VkFenceCreateInfo fenceCreateInfo = {};
		fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		fenceCreateInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;
		if (m_SyncObjects.InFlightFence == VK_NULL_HANDLE)
			VK_CHECK_RESULT(vkCreateFence(device, &fenceCreateInfo, nullptr, &m_SyncObjects.InFlightFence));

		VkAttachmentDescription colorAttachmentDesc = {};

		colorAttachmentDesc.format = m_ColorFormat;
		colorAttachmentDesc.samples = VK_SAMPLE_COUNT_1_BIT;
		colorAttachmentDesc.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		colorAttachmentDesc.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		colorAttachmentDesc.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		colorAttachmentDesc.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		colorAttachmentDesc.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		colorAttachmentDesc.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

		VkAttachmentReference colorAttachmentRef = {};
		colorAttachmentRef.attachment = 0;
		colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

		VkSubpassDescription subpassDesc = {};
		subpassDesc.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		subpassDesc.colorAttachmentCount = 1;
		subpassDesc.pColorAttachments = &colorAttachmentRef;

		VkSubpassDependency dependency = {};
		dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
		dependency.dstSubpass = 0;
		dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		dependency.srcAccessMask = 0;
		dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
		
		VkRenderPassCreateInfo renderPassInfo = {};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		renderPassInfo.attachmentCount = 1;
		renderPassInfo.pAttachments = &colorAttachmentDesc;
		renderPassInfo.subpassCount = 1;
		renderPassInfo.pSubpasses = &subpassDesc;
		renderPassInfo.dependencyCount = 1;
		renderPassInfo.pDependencies = &dependency;

		if (m_RenderPass == VK_NULL_HANDLE)
			VK_CHECK_RESULT(vkCreateRenderPass(device, &renderPassInfo, nullptr, &m_RenderPass));

		if (m_Framebuffers.empty())
		{
			VkFramebufferCreateInfo framebufferInfo = {};
			framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
			framebufferInfo.renderPass = m_RenderPass;
			framebufferInfo.attachmentCount = 1;
			framebufferInfo.width = m_Width;
			framebufferInfo.height = m_Height;
			framebufferInfo.layers = 1;

			m_Framebuffers.resize(m_ImageCount);

			for (uint32_t i = 0; i < m_ImageCount; i++)
			{
				VkImageView attachments[] = { m_Images[i].ImageView };
				framebufferInfo.pAttachments = attachments;
				VK_CHECK_RESULT(vkCreateFramebuffer(device, &framebufferInfo, nullptr, &m_Framebuffers[i]));
			}
		}

		
	}

	void VulkanSwapchain::Recreate(uint32_t width, uint32_t height, bool vsync)
	{ 
		m_Width = width;
		m_Height = height;
		m_VSync = vsync;

		VkDevice device = m_Device->GetVulkanDevice();
		
		vkDeviceWaitIdle(device);

		vkDestroySemaphore(device, m_SyncObjects.ImageAvailable, nullptr);
		m_SyncObjects.ImageAvailable = VK_NULL_HANDLE;
		vkDestroySemaphore(device, m_SyncObjects.RenderComplete, nullptr);
		m_SyncObjects.RenderComplete = VK_NULL_HANDLE;
		vkDestroyFence(device, m_SyncObjects.InFlightFence, nullptr);
		m_SyncObjects.InFlightFence = VK_NULL_HANDLE;

		vkDestroyCommandPool(device, m_CommandPool, nullptr);
		m_CommandPool = VK_NULL_HANDLE;

		for (auto& framebuffer : m_Framebuffers)
			vkDestroyFramebuffer(device, framebuffer, nullptr);
		m_Framebuffers.clear();
		

		vkDestroyRenderPass(device, m_RenderPass, nullptr);
		m_RenderPass = VK_NULL_HANDLE;

		for (auto& image : m_Images)
			vkDestroyImageView(device, image.ImageView, nullptr);
		m_Images.clear();

		vkDestroySwapchainKHR(device, m_Swapchain, nullptr);
		m_Swapchain = VK_NULL_HANDLE;

		Create(width, height, vsync);
	}
	
	void VulkanSwapchain::Destroy()
	{
		VkDevice device = m_Device->GetVulkanDevice();

		vkDeviceWaitIdle(device);
		
		for (auto& framebuffer : m_Framebuffers)
			vkDestroyFramebuffer(device, framebuffer, nullptr);

		vkDestroyRenderPass(device, m_RenderPass, nullptr);

		vkDestroyFence(device, m_SyncObjects.InFlightFence, nullptr);
		vkDestroySemaphore(device, m_SyncObjects.RenderComplete, nullptr);
		vkDestroySemaphore(device, m_SyncObjects.ImageAvailable, nullptr);

		vkDestroyCommandPool(device, m_CommandPool, nullptr);

		for (auto& image : m_Images)
			vkDestroyImageView(device, image.ImageView, nullptr);
		
		vkDestroySwapchainKHR(device, m_Swapchain, nullptr);
	}

	void VulkanSwapchain::Resize(uint32_t width, uint32_t height)
	{
		Recreate(width, height);
	}
	
	// When currentImageIndex is a member, for some reason, it doesnt store the value properly
	// So i gave up on trying to find why and just made it here
	uint32_t currentImageIndex;
	
	void VulkanSwapchain::BeginFrame()
	{
		VkDevice device = m_Device->GetVulkanDevice();

		vkWaitForFences(device, 1, &m_SyncObjects.InFlightFence, VK_TRUE, UINT64_MAX);
		vkResetFences(device, 1, &m_SyncObjects.InFlightFence);

		VK_CHECK_RESULT(vkAcquireNextImageKHR(device, m_Swapchain, UINT64_MAX, m_SyncObjects.ImageAvailable, VK_NULL_HANDLE, &currentImageIndex));

		VK_CHECK_RESULT(vkResetCommandBuffer(m_CommandBuffer, 0));

		VkCommandBufferBeginInfo beginInfo = {};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		
		VK_CHECK_RESULT(vkBeginCommandBuffer(m_CommandBuffer, &beginInfo));

		VkRenderPassBeginInfo renderPassInfo = {};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass = m_RenderPass;
		renderPassInfo.framebuffer = m_Framebuffers[currentImageIndex];
		renderPassInfo.renderArea.offset = { 0, 0 };
		renderPassInfo.renderArea.extent = { m_Width, m_Height };

		VkClearValue clearColor = { 1.0f, 0.0f, 1.0f, 1.0f };
		renderPassInfo.clearValueCount = 1;
		renderPassInfo.pClearValues = &clearColor;
		
		vkCmdBeginRenderPass(m_CommandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
	}
	
	void VulkanSwapchain::Present()
	{
		vkCmdEndRenderPass(m_CommandBuffer);

		VK_CHECK_RESULT(vkEndCommandBuffer(m_CommandBuffer));

		VkSubmitInfo submitInfo = {};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

		VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
		
		submitInfo.waitSemaphoreCount = 1;
		submitInfo.pWaitSemaphores = &m_SyncObjects.ImageAvailable;
		submitInfo.pWaitDstStageMask = waitStages;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &m_CommandBuffer;
		submitInfo.signalSemaphoreCount = 1;
		submitInfo.pSignalSemaphores = &m_SyncObjects.RenderComplete;

		VK_CHECK_RESULT(vkQueueSubmit(m_Device->GetGraphicsQueue(), 1, &submitInfo, m_SyncObjects.InFlightFence));

		VkPresentInfoKHR presentInfo = {};
		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		presentInfo.waitSemaphoreCount = 1;
		presentInfo.pWaitSemaphores = &m_SyncObjects.RenderComplete;
		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = &m_Swapchain;
		presentInfo.pImageIndices = &currentImageIndex;

		VK_CHECK_RESULT(vkQueuePresentKHR(m_Device->GetGraphicsQueue(), &presentInfo));
	}
	
	VkCommandBuffer& VulkanSwapchain::GetCurrentCommandBuffer()
	{
		// When using multiple command buffers, this should return the current one, hence CurrentCommandBuffer
		return m_CommandBuffer;
	}
	
	void VulkanSwapchain::CreateSurface(void* windowHandle)
	{
#ifdef AT_PLATFORM_WINDOWS
		HWND hWnd = (HWND)windowHandle;

		VkWin32SurfaceCreateInfoKHR createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
		createInfo.hinstance = GetModuleHandle(0);
		createInfo.hwnd = hWnd;

		VK_CHECK_RESULT(vkCreateWin32SurfaceKHR(m_Instance, &createInfo, nullptr, &m_Surface));
#endif
	}
	
	void VulkanSwapchain::DestroySurface()
	{
		vkDestroySurfaceKHR(m_Instance, m_Surface, nullptr);
	}
}
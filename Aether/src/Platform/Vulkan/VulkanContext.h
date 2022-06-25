#pragma once

#include "Renderer/GraphicsContext.h"

#include "Vulkan.h"

#include "VulkanDevice.h"

namespace Aether {
	class VulkanContext : public GraphicsContext
	{
	public:
		VulkanContext(void* window);
		virtual ~VulkanContext() override;

		virtual void Init() override;
		virtual void SwapBuffers() override;

		static VkInstance GetInstance() { return s_VulkanInstance; }
	private:
		void* m_Window;

		inline static VkInstance s_VulkanInstance;
		VkDebugReportCallbackEXT m_DebugReportCallback = VK_NULL_HANDLE;
		VkSurfaceKHR m_Surface;

		Scope<VulkanPhysicalDevice> m_PhysicalDevice;
		Scope<VulkanDevice> m_Device;
	};
}
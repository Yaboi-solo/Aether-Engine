#pragma once

#include "Renderer/GraphicsContext.h"

#include "Vulkan.h"
#include "VulkanDevice.h"


#include "Renderer/Renderer.h"

namespace Aether {
	class VulkanContext : public GraphicsContext
	{
	public:
		VulkanContext(void* window);
		virtual ~VulkanContext() override;

		virtual void Init() override;
		virtual void SwapBuffers() override;

		Ref<VulkanDevice> GetDevice() { return m_Device; }
		
		static VkInstance GetInstance() { return s_VulkanInstance; }

		static VulkanContext& Get() { return dynamic_cast<VulkanContext&>((*Renderer::GetContext())); }
	private:
		void* m_Window;

		inline static VkInstance s_VulkanInstance = nullptr;
		VkDebugReportCallbackEXT m_DebugReportCallback = nullptr;
		VkSurfaceKHR m_Surface = nullptr;

		Ref<VulkanPhysicalDevice> m_PhysicalDevice;
		Ref<VulkanDevice> m_Device;
	};
}
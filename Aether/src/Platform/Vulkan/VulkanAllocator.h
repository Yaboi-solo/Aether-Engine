#pragma once

#include "Vulkan.h"
#include "VulkanDevice.h"

namespace Aether {
	class VulkanAllocator
	{
	public:
		VulkanAllocator() = default;
		VulkanAllocator(const Ref<VulkanDevice>& device, const std::string& tag = "");
		~VulkanAllocator();

		void Allocator(VkMemoryRequirements requirements, VkDeviceMemory* dest, VkMemoryPropertyFlags flags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
	private:
		Ref<VulkanDevice> m_Device;
		std::string m_Tag;
	};
}
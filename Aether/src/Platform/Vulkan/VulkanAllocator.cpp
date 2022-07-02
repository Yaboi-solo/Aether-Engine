#include "atpch.h"
#include "VulkanAllocator.h"

namespace Aether {
	VulkanAllocator::VulkanAllocator(const Ref<VulkanDevice>& device, const std::string& tag)
		: m_Device(device), m_Tag(tag)
	{
	}

	VulkanAllocator::~VulkanAllocator()
	{
	}

	void VulkanAllocator::Allocator(VkMemoryRequirements requirements, VkDeviceMemory* dest, VkMemoryPropertyFlags flags)
	{
		AT_ASSERT(m_Device, "");

		AT_TRACE("VulkanAllocator ({0}): Allocating {1} bytes", m_Tag, requirements.size);

		VkMemoryAllocateInfo memAlloc{};
		memAlloc.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		memAlloc.allocationSize = requirements.size;
		memAlloc.memoryTypeIndex = m_Device->GetPhysicalDevice()->GetMemoryTypeIndex(requirements.memoryTypeBits, flags);
		VK_CHECK_RESULT(vkAllocateMemory(m_Device->GetVulkanDevice(), &memAlloc, nullptr, dest));
	}
}  
#pragma once

#include <vulkan/vulkan.h>

#define VK_CHECK_RESULT(f)																\
{																						\
	VkResult res = (f);																	\
	if (res != VK_SUCCESS)																\
	{																					\
		AT_FATAL("VkResult is '{0}' in file {1}:{2}", (int)res, __FILE__, __LINE__);	\
		AT_ASSERT(res == VK_SUCCESS, "");												\
	}																					\
}

namespace Aether {
	void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
	void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
}
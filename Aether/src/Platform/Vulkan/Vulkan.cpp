#include "atpch.h"
#include "Vulkan.h"

#include "VulkanContext.h"

namespace Aether {
	void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory)
	{
		VkBufferCreateInfo bufferInfo = {};
		bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bufferInfo.size = size;
		bufferInfo.usage = usage;
		bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		VK_CHECK_RESULT(vkCreateBuffer(VulkanContext::Get()->GetDevice()->GetVulkanDevice(), &bufferInfo, nullptr, &buffer));

		VkMemoryRequirements memRequirements;
		vkGetBufferMemoryRequirements(VulkanContext::Get()->GetDevice()->GetVulkanDevice(), buffer, &memRequirements);

		VkMemoryAllocateInfo allocInfo = {};
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		allocInfo.allocationSize = memRequirements.size;
		allocInfo.memoryTypeIndex = VulkanContext::Get()->GetDevice()->GetPhysicalDevice()->GetMemoryTypeIndex(memRequirements.memoryTypeBits, properties);

		VK_CHECK_RESULT(vkAllocateMemory(VulkanContext::Get()->GetDevice()->GetVulkanDevice(), &allocInfo, nullptr, &bufferMemory));

		VK_CHECK_RESULT(vkBindBufferMemory(VulkanContext::Get()->GetDevice()->GetVulkanDevice(), buffer, bufferMemory, 0));
	}

	void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size)
	{
		VkCommandBufferAllocateInfo allocInfo = {};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandPool = VulkanContext::Get()->GetTransferCommandPool();
		allocInfo.commandBufferCount = 1;

		VkCommandBuffer commandBuffer;
		VK_CHECK_RESULT(vkAllocateCommandBuffers(VulkanContext::Get()->GetDevice()->GetVulkanDevice(), &allocInfo, &commandBuffer));

		VkCommandBufferBeginInfo beginInfo = {};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

		VK_CHECK_RESULT(vkBeginCommandBuffer(commandBuffer, &beginInfo));

		VkBufferCopy copyRegion = {};
		copyRegion.size = size;
		vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

		VK_CHECK_RESULT(vkEndCommandBuffer(commandBuffer));

		VkSubmitInfo submitInfo = {};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &commandBuffer;

		VK_CHECK_RESULT(vkQueueSubmit(VulkanContext::Get()->GetDevice()->GetTransferQueue(), 1, &submitInfo, VK_NULL_HANDLE));
		VK_CHECK_RESULT(vkQueueWaitIdle(VulkanContext::Get()->GetDevice()->GetTransferQueue()));

		vkFreeCommandBuffers(VulkanContext::Get()->GetDevice()->GetVulkanDevice(), VulkanContext::Get()->GetTransferCommandPool(), 1, &commandBuffer);
	}
}
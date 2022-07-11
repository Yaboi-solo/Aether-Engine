#include "atpch.h"
#include "VulkanIndexBuffer.h"

#include "VulkanContext.h"

namespace Aether {
	VulkanIndexBuffer::VulkanIndexBuffer(void* data, uint32_t size)
		: m_Size(size)
	{
		auto device = VulkanContext::Get()->GetDevice();

#ifdef USE_STAGING
		VkBuffer stagingBuffer;
		VkDeviceMemory stagingBufferMemory;
		CreateBuffer(size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

		void* mapped;
		vkMapMemory(device->GetVulkanDevice(), stagingBufferMemory, 0, size, 0, &mapped);
		memcpy(mapped, data, size);
		vkUnmapMemory(device->GetVulkanDevice(), stagingBufferMemory);

		CreateBuffer(size, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_Buffer, m_DeviceMemory);

		CopyBuffer(stagingBuffer, m_Buffer, size);
		
		vkDestroyBuffer(device->GetVulkanDevice(), stagingBuffer, nullptr);
		vkFreeMemory(device->GetVulkanDevice(), stagingBufferMemory, nullptr);
#else
		CreateBuffer(size, VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, m_Buffer, m_DeviceMemory);

		void* mapped;
		vkMapMemory(device->GetVulkanDevice(), m_DeviceMemory, 0, size, 0, &mapped);
		memcpy(mapped, data, size);
		vkUnmapMemory(device->GetVulkanDevice(), m_DeviceMemory);
#endif
	}

	VulkanIndexBuffer::~VulkanIndexBuffer()
	{
		vkDeviceWaitIdle(VulkanContext::Get()->GetDevice()->GetVulkanDevice());

		vkDestroyBuffer(VulkanContext::Get()->GetDevice()->GetVulkanDevice(), m_Buffer, nullptr);
		vkFreeMemory(VulkanContext::Get()->GetDevice()->GetVulkanDevice(), m_DeviceMemory, nullptr);
	}
	
	void VulkanIndexBuffer::SetData(void* buffer, uint32_t size, uint32_t offset)
	{
		void* data;
		vkMapMemory(VulkanContext::Get()->GetDevice()->GetVulkanDevice(), m_DeviceMemory, 0, size, 0, &data);
		memcpy(data, buffer, size);
		vkUnmapMemory(VulkanContext::Get()->GetDevice()->GetVulkanDevice(), m_DeviceMemory);
	}
	
	void VulkanIndexBuffer::Bind() const
	{
		vkCmdBindIndexBuffer(VulkanContext::Get()->GetSwapchain()->GetCurrentCommandBuffer(), m_Buffer, 0, VK_INDEX_TYPE_UINT32);
	}
}
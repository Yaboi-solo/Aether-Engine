#pragma once

#include "Renderer/IndexBuffer.h"

#include "Vulkan.h"

namespace Aether {
	class VulkanIndexBuffer : public IndexBuffer
	{
	public:
		VulkanIndexBuffer(void* data, uint32_t size);
		virtual ~VulkanIndexBuffer() override;

		virtual void SetData(void* buffer, uint32_t size, uint32_t offset) override;
		virtual void Bind() const override;

		virtual uint32_t GetCount() const override { return m_Size / sizeof(uint32_t); }
		virtual uint32_t GetSize() const override { return m_Size;  }
	private:
		uint32_t m_Size;

		VkBuffer m_Buffer = nullptr;
		VkDeviceMemory m_DeviceMemory = nullptr;
	};
}
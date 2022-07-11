#pragma once

#include "Vulkan.h"

#include "Renderer/VertexBuffer.h"

namespace Aether {
	class VulkanVertexBuffer : public VertexBuffer
	{
	public:
		VulkanVertexBuffer(void* data, uint32_t size, VertexBufferUsage usage);
		virtual ~VulkanVertexBuffer() override;

		virtual void SetData(void* buffer, uint32_t size, uint32_t offset) override;
		virtual void Bind() const override;

		virtual uint32_t GetSize() const override { return m_Size; }
	private:
		uint32_t m_Size;

		VkBuffer m_Buffer = nullptr;
		VkDeviceMemory m_DeviceMemory = nullptr;
	};
}
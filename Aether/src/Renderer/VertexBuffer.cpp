#include "atpch.h"
#include "VertexBuffer.h"

#include "RendererAPI.h"

#include "Platform/Vulkan/VulkanVertexBuffer.h"

namespace Aether {
	Ref<VertexBuffer> VertexBuffer::Create(void* data, uint32_t size, VertexBufferUsage usage)
	{
		switch (RendererAPI::GetCurrentAPI())
		{
		case RendererAPI::None: AT_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
		case RendererAPI::Vulkan: return CreateRef<VulkanVertexBuffer>(data, size, usage);
		}

		AT_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
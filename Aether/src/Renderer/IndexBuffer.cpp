#include "atpch.h"
#include "IndexBuffer.h"

#include "RendererAPI.h"

#include "Platform/Vulkan/VulkanIndexBuffer.h"

namespace Aether {
	Ref<IndexBuffer> IndexBuffer::Create(void* data, uint32_t size)
	{
		switch (RendererAPI::GetCurrentAPI())
		{
		case RendererAPI::None: AT_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
		case RendererAPI::Vulkan: return CreateRef<VulkanIndexBuffer>(data, size);
		}


		AT_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
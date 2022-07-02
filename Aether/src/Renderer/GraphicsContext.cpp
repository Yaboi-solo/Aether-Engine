#include "atpch.h"
#include "GraphicsContext.h"

#include "RendererAPI.h"

#include "Platform/Vulkan/VulkanContext.h"

namespace Aether {
	Ref<GraphicsContext> GraphicsContext::Create(void* window, uint32_t width, uint32_t height)
	{
		switch (RendererAPI::GetCurrentAPI())
		{
		case RendererAPI::None: AT_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
		case RendererAPI::Vulkan: return CreateRef<VulkanContext>(window, width, height);
		}

		AT_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
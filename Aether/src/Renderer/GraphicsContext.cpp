#include "atpch.h"
#include "GraphicsContext.h"

#include "RendererAPI.h"

#include "Platform/Vulkan/VulkanContext.h"

namespace Aether {
	Ref<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (RendererAPI::GetCurrentAPI())
		{
		case RendererAPI::None: AT_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
		case RendererAPI::Vulkan: return CreateRef<VulkanContext>(window);
		}

		AT_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
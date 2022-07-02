#include "atpch.h"
#include "RendererAPI.h"

#include "Platform/Vulkan/VulkanRendererAPI.h"

namespace Aether {
	RendererAPI::API RendererAPI::s_API = RendererAPI::Vulkan;

	Ref<RendererAPI> RendererAPI::Create()
	{
		switch (RendererAPI::GetCurrentAPI())
		{
		case RendererAPI::None: AT_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
		case RendererAPI::Vulkan: return CreateRef<VulkanRendererAPI>();
		}
	}
}
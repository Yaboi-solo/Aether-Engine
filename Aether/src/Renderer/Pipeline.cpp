#include "atpch.h"
#include "Pipeline.h"

#include "RendererAPI.h"

#include "Platform/Vulkan/VulkanPipeline.h"

namespace Aether {
	Ref<Pipeline> Pipeline::Create(const PipelineSpecification& spec)
	{
		switch (RendererAPI::GetCurrentAPI())
		{
		case RendererAPI::None: AT_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
		case RendererAPI::Vulkan: return CreateRef<VulkanPipeline>(spec);
		}

		AT_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
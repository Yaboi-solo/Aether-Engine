#pragma once

#include "Renderer/RendererAPI.h"

#include "VulkanContext.h"

namespace Aether {
	class VulkanRendererAPI : public RendererAPI
	{
	public:
		virtual void Init() override;
		virtual void Shutdown() override;

		virtual void BeginFrame() override;
		virtual void EndFrame() override;
		
		virtual void Resize(uint32_t width, uint32_t height) override;
	private:
		Ref<VulkanContext> m_Context;
	};
}
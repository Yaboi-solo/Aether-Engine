#pragma once

#include "Renderer/Pipeline.h"

#include "Vulkan.h"

namespace Aether {
	class VulkanPipeline : public Pipeline
	{
	public:
		VulkanPipeline(const PipelineSpecification& spec);
		virtual ~VulkanPipeline() override;

		virtual PipelineSpecification& GetSpecification() override { return m_Spec; }
		virtual const PipelineSpecification& GetSpecification() const override { return m_Spec; }
		
		virtual void Bind() override;
	private:
		VkPipeline m_Pipeline;
		VkPipelineLayout m_PipelineLayout;

		PipelineSpecification m_Spec;
	};
}
#include "atpch.h"
#include "VulkanPipeline.h"

#include "VulkanShader.h"

#include "VulkanContext.h"

namespace Aether {

	namespace Utils
	{
		static VkPrimitiveTopology GetVulkanTopology(PrimitiveTopology topology)
		{
			switch (topology)
			{
			case PrimitiveTopology::Points: return VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
			case PrimitiveTopology::Lines: return VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
			case PrimitiveTopology::Triangles: return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
			case PrimitiveTopology::LineStrip: return VK_PRIMITIVE_TOPOLOGY_LINE_STRIP;
			case PrimitiveTopology::TriangleStrip: return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;
			case PrimitiveTopology::TriangleFan: return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN;
			}

			AT_ASSERT(false, "Unknown primitive topology!");
			return VK_PRIMITIVE_TOPOLOGY_MAX_ENUM;
		}

		static VkFormat ShaderDataTypeToVkFormat(ShaderDataType type)
		{
			switch (type)
			{
			case ShaderDataType::Float: return VK_FORMAT_R32_SFLOAT;
			case ShaderDataType::Float2:    return VK_FORMAT_R32G32_SFLOAT;
			case ShaderDataType::Float3:    return VK_FORMAT_R32G32B32_SFLOAT;
			case ShaderDataType::Float4:    return VK_FORMAT_R32G32B32A32_SFLOAT;
			}

			AT_ASSERT(false, "Unknown ShaderDataType!");
			return VK_FORMAT_UNDEFINED;
		}
	}

	

	VulkanPipeline::VulkanPipeline(const PipelineSpecification& spec)
		: m_Spec(spec)
	{
		auto shader = std::dynamic_pointer_cast<VulkanShader, Shader>(spec.Shader);

		VkPipelineShaderStageCreateInfo vertShaderStageInfo = {};
		vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
		vertShaderStageInfo.module = shader->GetVertexModule();
		vertShaderStageInfo.pName = "main";

		VkPipelineShaderStageCreateInfo fragShaderStageInfo = {};
		fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
		fragShaderStageInfo.module = shader->GetFragmentModule();
		fragShaderStageInfo.pName = "main";
		
		VkPipelineShaderStageCreateInfo shaderStages[] = { vertShaderStageInfo, fragShaderStageInfo };
		

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
		vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

		VkVertexInputBindingDescription vertexBindingDescription = {};
		vertexBindingDescription.binding = 0;
		vertexBindingDescription.stride = spec.Layout.GetStride();
		vertexBindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

		std::vector<VkVertexInputAttributeDescription> vertexAttributeDescription(spec.Layout.GetElementCount());
		int i = 0;
		for (auto& element : spec.Layout.GetElements())
		{
			vertexAttributeDescription[i].binding = 0;
			vertexAttributeDescription[i].location = i;
			vertexAttributeDescription[i].format = Utils::ShaderDataTypeToVkFormat(element.Type);
			vertexAttributeDescription[i].offset = element.Offset;
			i++;
		}
		
		vertexInputInfo.vertexBindingDescriptionCount = 1;
		vertexInputInfo.pVertexBindingDescriptions = &vertexBindingDescription;
		vertexInputInfo.vertexAttributeDescriptionCount = (uint32_t)vertexAttributeDescription.size();
		vertexInputInfo.pVertexAttributeDescriptions = vertexAttributeDescription.data();

		VkPipelineInputAssemblyStateCreateInfo inputAssembly = {};
		inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		inputAssembly.topology = Utils::GetVulkanTopology(spec.Topology);
		inputAssembly.primitiveRestartEnable = VK_FALSE;
		
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		VkViewport viewport = {};
		viewport.x = 0.0f;
		viewport.y = 0.0f;
		viewport.width = (float)Application::Get().GetWindow().GetWidth();
		viewport.height = (float)Application::Get().GetWindow().GetHeight();
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;
		
		VkRect2D scissor = {};
		scissor.offset = { 0, 0 };
		scissor.extent = { (uint32_t)Application::Get().GetWindow().GetWidth(), (uint32_t)Application::Get().GetWindow().GetHeight() };
		
		VkPipelineViewportStateCreateInfo viewportState = {};
		viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		viewportState.viewportCount = 1;
		viewportState.pViewports = &viewport;
		viewportState.scissorCount = 1;
		viewportState.pScissors = &scissor;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		VkPipelineRasterizationStateCreateInfo rasterizer = {};
		rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		rasterizer.polygonMode = spec.Wireframe ? VK_POLYGON_MODE_LINE : VK_POLYGON_MODE_FILL;
		rasterizer.lineWidth = spec.LineWidth;
		rasterizer.cullMode = spec.BackfaceCulling ? VK_CULL_MODE_BACK_BIT : VK_CULL_MODE_NONE;
		rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
		rasterizer.depthClampEnable = VK_FALSE;
		rasterizer.rasterizerDiscardEnable = VK_FALSE;
		rasterizer.depthBiasEnable = VK_FALSE;

		VkPipelineMultisampleStateCreateInfo multisampling = {};
		multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		multisampling.sampleShadingEnable = VK_FALSE;
		multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

		VkPipelineDepthStencilStateCreateInfo depthStencil = {};
		depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
		depthStencil.depthTestEnable = VK_TRUE;
		depthStencil.depthWriteEnable = VK_TRUE;
		depthStencil.depthCompareOp = VK_COMPARE_OP_LESS;
		depthStencil.depthBoundsTestEnable = VK_FALSE;
		depthStencil.stencilTestEnable = VK_FALSE;
		
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
		colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
		colorBlendAttachment.blendEnable = VK_TRUE;
		colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
		colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
		colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
		colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
		colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
		colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;

		VkPipelineColorBlendStateCreateInfo colorBlending = {};
		colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		colorBlending.logicOpEnable = VK_FALSE;
		colorBlending.logicOp = VK_LOGIC_OP_COPY;
		colorBlending.attachmentCount = 1;
		colorBlending.pAttachments = &colorBlendAttachment;
		colorBlending.blendConstants[0] = 0.0f;
		colorBlending.blendConstants[1] = 0.0f;
		colorBlending.blendConstants[2] = 0.0f;
		colorBlending.blendConstants[3] = 0.0f;
		
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo.setLayoutCount = 0;
		pipelineLayoutInfo.pSetLayouts = nullptr;
		pipelineLayoutInfo.pushConstantRangeCount = 0;
		pipelineLayoutInfo.pPushConstantRanges = nullptr;

		VK_CHECK_RESULT(vkCreatePipelineLayout(VulkanContext::Get()->GetDevice()->GetVulkanDevice(), &pipelineLayoutInfo, nullptr, &m_PipelineLayout));

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		VkGraphicsPipelineCreateInfo pipelineCreateInfo = {};
		pipelineCreateInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;

		pipelineCreateInfo.stageCount = (uint32_t)sizeof(shaderStages) / sizeof(shaderStages[0]);
		pipelineCreateInfo.pStages = shaderStages;

		pipelineCreateInfo.pVertexInputState = &vertexInputInfo;
		pipelineCreateInfo.pInputAssemblyState = &inputAssembly;
		pipelineCreateInfo.pViewportState = &viewportState;
		pipelineCreateInfo.pRasterizationState = &rasterizer;
		pipelineCreateInfo.pMultisampleState = &multisampling;
		pipelineCreateInfo.pDepthStencilState = &depthStencil;
		pipelineCreateInfo.pColorBlendState = &colorBlending;
		pipelineCreateInfo.pDynamicState = nullptr;
		
		pipelineCreateInfo.layout = m_PipelineLayout;
		
		pipelineCreateInfo.renderPass = VulkanContext::Get()->GetSwapchain()->GetRenderpass();
		pipelineCreateInfo.subpass = 0;

		pipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;
		pipelineCreateInfo.basePipelineIndex = -1;

		VK_CHECK_RESULT(vkCreateGraphicsPipelines(VulkanContext::Get()->GetDevice()->GetVulkanDevice(), VK_NULL_HANDLE, 1, &pipelineCreateInfo, nullptr, &m_Pipeline));		
	}
	
	VulkanPipeline::~VulkanPipeline()
	{
		vkQueueWaitIdle(VulkanContext::Get()->GetDevice()->GetGraphicsQueue());
		
		vkDestroyPipeline(VulkanContext::Get()->GetDevice()->GetVulkanDevice(), m_Pipeline, nullptr);
		vkDestroyPipelineLayout(VulkanContext::Get()->GetDevice()->GetVulkanDevice(), m_PipelineLayout, nullptr);
	}

	void VulkanPipeline::Bind()
	{
		vkCmdBindPipeline(VulkanContext::Get()->GetSwapchain()->GetCurrentCommandBuffer(), VK_PIPELINE_BIND_POINT_GRAPHICS, m_Pipeline);
	}
}
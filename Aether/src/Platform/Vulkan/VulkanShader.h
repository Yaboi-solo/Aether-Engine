#pragma once


#include "Renderer/Shader.h"

#include "Vulkan.h"

namespace Aether {
	class VulkanShader : public Shader
	{
	public:
		VulkanShader(const std::string& filepath);
		virtual ~VulkanShader() override;

		virtual const std::string& GetName() const override { return m_Name; }
		
		VkShaderModule GetVertexModule() { return m_VertexShaderModule; }
		VkShaderModule GetFragmentModule() { return m_FragmentShaderModule; }
	private:
		std::string m_Name;

		VkShaderModule m_VertexShaderModule;
		VkShaderModule m_FragmentShaderModule;
	};
}
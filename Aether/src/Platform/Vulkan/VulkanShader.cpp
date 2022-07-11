#include "atpch.h"
#include "VulkanShader.h"

#include "shaderc/shaderc.hpp"

#include "VulkanContext.h"

#include "Core/Timer.h"

namespace Aether {
	VulkanShader::VulkanShader(const std::string& filepath)
	{
		auto src = Shader::LoadFromFile(filepath);

		m_Name = src.Filename;

		Timer timer;
		
		shaderc::Compiler compiler;
		
		shaderc::CompileOptions options;
		options.SetSourceLanguage(shaderc_source_language_glsl);
		options.SetOptimizationLevel(shaderc_optimization_level_performance);
		options.SetWarningsAsErrors();

		shaderc::CompilationResult vertexResult = compiler.CompileGlslToSpv(src.VertexSource.c_str(), src.VertexSource.length(), shaderc_glsl_vertex_shader, "vertexShader", "main", options);
		if (vertexResult.GetCompilationStatus() != shaderc_compilation_status_success)
		{
			AT_ERROR("Failed to vertex compile shader: {0}", src.Filename);
			AT_ERROR("{0}", vertexResult.GetErrorMessage());
			AT_ASSERT(false, "");
			return;
		}
		std::vector<uint32_t> vertex(vertexResult.cbegin(), vertexResult.cend());

		shaderc::CompilationResult fragmentResult = compiler.CompileGlslToSpv(src.FragmentSource.c_str(), src.FragmentSource.length(), shaderc_glsl_fragment_shader, "fragmentShader", "main", options);
		if (fragmentResult.GetCompilationStatus() != shaderc_compilation_status_success)
		{
			AT_ERROR("Failed to fragment compile shader: {0}", src.Filename);
			AT_ERROR("{0}", fragmentResult.GetErrorMessage());
			AT_ASSERT(false, "");
			return;
		}
		std::vector<uint32_t> fragment(fragmentResult.cbegin(), fragmentResult.cend());

		AT_WARN("Shader '{0}' took {1} seconds to compile...", m_Name, timer.GetElapsed());

		VkShaderModuleCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;

		createInfo.codeSize = vertex.size() * sizeof(uint32_t);
		createInfo.pCode = vertex.data();
		
		VK_CHECK_RESULT(vkCreateShaderModule(VulkanContext::Get()->GetDevice()->GetVulkanDevice(), &createInfo, nullptr, &m_VertexShaderModule));
		
		createInfo.codeSize = fragment.size() * sizeof(uint32_t);
		createInfo.pCode = fragment.data();

		VK_CHECK_RESULT(vkCreateShaderModule(VulkanContext::Get()->GetDevice()->GetVulkanDevice(), &createInfo, nullptr, &m_FragmentShaderModule));
	}
	
	VulkanShader::~VulkanShader()
	{
		vkDestroyShaderModule(VulkanContext::Get()->GetDevice()->GetVulkanDevice(), m_VertexShaderModule, nullptr);
		vkDestroyShaderModule(VulkanContext::Get()->GetDevice()->GetVulkanDevice(), m_FragmentShaderModule, nullptr);
	}
}
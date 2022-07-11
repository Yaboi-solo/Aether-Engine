#include "atpch.h"
#include "Shader.h"

#include <filesystem>

#include "RendererAPI.h"

#include "Platform/Vulkan/VulkanShader.h"

namespace Aether {
	ShaderSourceData Shader::LoadFromFile(const std::string& filepath)
	{
		std::ifstream stream(filepath);

		enum class ShaderType
		{
			NONE = -1,
			VERTEX = 0,
			FRAGMENT = 1
		};

		std::string line;
		std::stringstream ss[2];
		ShaderType type = ShaderType::NONE;
		
		while (getline(stream, line))
		{
			if (line.find("#type") != std::string::npos)
			{
				if (line.find("vertex") != std::string::npos)
					type = ShaderType::VERTEX;
				else if (line.find("fragment") != std::string::npos)
					type = ShaderType::FRAGMENT;
			}
			else
			{
				ss[(int)type] << line << '\n';
			}
		}

		//AT_TRACE("{0}\n\n {1}\n\n FILE: {2}", ss[0].str(), ss[1].str(), std::filesystem::path(filepath).stem().string());
		//AT_INFO("CWD: {0}", std::filesystem::current_path().string());

		return { ss[0].str(), ss[1].str(), std::filesystem::path(filepath).stem().string() };
	}
	
	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (RendererAPI::GetCurrentAPI())
		{
		case RendererAPI::None: AT_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
		case RendererAPI::Vulkan: return CreateRef<VulkanShader>(filepath);
		}

		AT_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
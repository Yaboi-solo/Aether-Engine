#pragma once

namespace Aether {
	
	struct ShaderSourceData
	{
		std::string VertexSource;
		std::string FragmentSource;
		std::string Filename;
	};
	
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual const std::string& GetName() const = 0;

		static ShaderSourceData LoadFromFile(const std::string& filepath);

		static Ref<Shader> Create(const std::string& filepath);
	};
}
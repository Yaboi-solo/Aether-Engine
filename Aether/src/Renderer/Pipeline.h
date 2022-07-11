#pragma once

#include "Shader.h"
#include "VertexBuffer.h"

namespace Aether {
	enum class PrimitiveTopology
	{
		None = 0,
		Points,
		Lines,
		Triangles,
		LineStrip,
		TriangleStrip,
		TriangleFan
	};

	struct PipelineSpecification
	{
		Ref<Shader> Shader;
		VertexBufferLayout Layout;
		PrimitiveTopology Topology = PrimitiveTopology::Triangles;
		bool BackfaceCulling = false;
		bool DepthTest = false;
		bool Wireframe = false;
		float LineWidth = 1.0f;

		std::string Name;
	};

	class Pipeline
	{
	public:
		virtual ~Pipeline() = default;

		virtual PipelineSpecification& GetSpecification() = 0;
		virtual const PipelineSpecification& GetSpecification() const = 0;

		virtual void Bind() = 0;

		static Ref<Pipeline> Create(const PipelineSpecification& spec);
	};
}
#include "atpch.h"
#include "Renderer2D.h"

#include "Shader.h"

#include "Renderer.h"

namespace Aether {

	Renderer2D::Renderer2D()
	{
	}
	
	Renderer2D::~Renderer2D()
	{
	}
	
	void Renderer2D::Init()
	{
		float vertices[] = {
			-0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f,
			-0.5f,  0.5f, 1 .0f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f
			
		};

		uint32_t indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		m_VertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));

		m_IndexBuffer = IndexBuffer::Create(indices, sizeof(indices));

		PipelineSpecification spec;
		spec.Name = "Triangle";
		spec.Shader = Shader::Create("assets/shaders/Default.glsl");
		spec.BackfaceCulling = false;
		spec.Layout = {
			{ ShaderDataType::Float3, "a_Pos" },
			{ ShaderDataType::Float3, "a_Color"}
		};
		m_Pipeline = Pipeline::Create(spec);
	}
	
	void Renderer2D::Shutdown()
	{
	}
	
	void Renderer2D::BeginScene()
	{
	}
	
	void Renderer2D::EndScene()
	{
	}
	
	void Renderer2D::DrawQuad(const Matrix4f& transform, const Vector4f& color)
	{
		m_Pipeline->Bind();

		m_VertexBuffer->Bind();
		m_IndexBuffer->Bind();
		
		Renderer::DrawIndexed(m_IndexBuffer);
	}
}
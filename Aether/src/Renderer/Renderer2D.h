#pragma once

#include "Math/Math.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Pipeline.h"

namespace Aether {
	class Renderer2D
	{
	public:
		Renderer2D();
		virtual ~Renderer2D();

		void Init();
		void Shutdown();
		
		void BeginScene();
		void EndScene();

		void DrawQuad(const Matrix4f& transform, const Vector4f& color);
	private:
		Ref<Pipeline> m_Pipeline;

		Ref<VertexBuffer> m_VertexBuffer;
		Ref<IndexBuffer> m_IndexBuffer;
	};
}
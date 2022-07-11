#pragma once

namespace Aether {
	
	class GraphicsContext
	{
	public:
		virtual ~GraphicsContext() = default;

		virtual void Init() = 0;
		
		static Ref<GraphicsContext> Create(void* window, uint32_t width, uint32_t height);
	};
}
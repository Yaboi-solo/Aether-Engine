#pragma once

namespace Aether {
	class RendererAPI
	{
	public:
		enum API
		{
			None = 0,
			Vulkan = 1
		};
	public:
		virtual void Init() = 0;
		virtual void Shutdown() = 0;
		
		virtual void BeginFrame() = 0;
		virtual void EndFrame() = 0;

		virtual void Resize(uint32_t width, uint32_t height) = 0;

		static Ref<RendererAPI> Create();

		static API GetCurrentAPI() { return s_API; }
	private:
		static API s_API;
	};
}
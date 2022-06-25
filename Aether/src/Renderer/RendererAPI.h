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

		static API GetCurrentAPI() { return s_API; }
	private:
		static API s_API;
	};
}
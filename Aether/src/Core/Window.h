#pragma once

#include <string>

#include "Renderer/GraphicsContext.h"

namespace Aether {

	struct WindowProperties
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;

		WindowProperties(const std::string& title = "Aether-Engine",
			uint32_t width = 1600,
			uint32_t height = 900)
			: Title(title), Width(width), Height(height)
		{
		}
	};


	class Window
	{
	public:
		virtual ~Window() = default;
		
		virtual void Update() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void* GetNativeWindow() const = 0;

		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual Ref<GraphicsContext> GetGraphicsContext() = 0;

		static Scope<Window> Create(const WindowProperties& properties = WindowProperties());
	};
}
#pragma once

#include "Core/Window.h"

#define WIN32_MEAN_AND_LEAN
#include <Windows.h>

namespace Aether {
	class Win32Window : public Window
	{
	public:
		Win32Window(const WindowProperties& properties);
		virtual ~Win32Window() override;

		virtual void Update() override;

		virtual uint32_t GetWidth() const override { return m_Data.Width; }
		virtual uint32_t GetHeight() const override { return m_Data.Height; }

		virtual void* GetNativeWindow() const override { return (void*)m_hWnd; }

		virtual void SetVSync(bool enabled) override { m_Data.VSync = enabled; }
		virtual bool IsVSync() const override { return m_Data.VSync; }

		virtual Ref<GraphicsContext> GetGraphicsContext() override { return m_GraphicsContext; }
	private:
		virtual void Init();
		virtual void Shutdown();
	private:
		struct WindowData
		{
			uint32_t Width;
			uint32_t Height;
			std::string Title;
			bool VSync;
		};

		WindowData m_Data;

		HINSTANCE m_hInstance;
		HWND m_hWnd;

		Ref<GraphicsContext> m_GraphicsContext;
	};
}
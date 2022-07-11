#include "atpch.h"
#include "Win32Window.h"

#include "Event/ApplicationEvent.h"

namespace Aether {

	LRESULT CALLBACK Message_Proc(HWND hWnd, uint32_t msg, WPARAM wParam, LPARAM lParam);


	Win32Window::Win32Window(const WindowProperties& properties)
	{
		m_Data.Width = properties.Width;
		m_Data.Height = properties.Height;
		m_Data.Title = properties.Title;
		m_Data.VSync = false;

		Init();
	}

	Win32Window::~Win32Window()
	{
		Shutdown();
	}

	void Win32Window::Update()
	{
		MSG message;
		while (PeekMessageA(&message, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&message);
			DispatchMessageA(&message);
		}
	}

	void Win32Window::Init()
	{
		m_hInstance = GetModuleHandleA(0);

		HICON icon = LoadIcon(m_hInstance, IDI_APPLICATION);

		WNDCLASSA wc;
		memset(&wc, 0, sizeof(wc));
		wc.hInstance = m_hInstance;
		wc.style = CS_DBLCLKS; // Get double-clicks
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hIcon = icon;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW); // Manager cursor manually
		wc.hbrBackground = NULL; // Transparent
		wc.lpszClassName = "Aether_Window_Class";
		wc.lpfnWndProc = Message_Proc;

		if (!RegisterClassA(&wc)) {
			AT_FATAL("Faied to register window class!");
			return;
		}

		uint32_t window_x = ((GetSystemMetrics(SM_CXSCREEN) / 2) - (m_Data.Width / 2));
		uint32_t window_y = ((GetSystemMetrics(SM_CYSCREEN) / 2) - (m_Data.Height / 2));
		uint32_t window_width = m_Data.Width;
		uint32_t window_height = m_Data.Height;

		uint32_t window_style = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION;
		uint32_t window_ex_style = WS_EX_APPWINDOW;

		window_style |= WS_MAXIMIZEBOX;
		window_style |= WS_THICKFRAME;
		window_style |= WS_MINIMIZEBOX;

		RECT border_rect = { 0, 0, 0, 0 };
		AdjustWindowRectEx(&border_rect, window_style, 0, window_ex_style);

		window_x += border_rect.left;
		window_y += border_rect.top;

		window_width += border_rect.right - border_rect.left;
		window_height += border_rect.bottom - border_rect.top;

		AT_INFO("Creating window '{0}' ( {1} / {2} )", m_Data.Title, m_Data.Width, m_Data.Height);

		m_hWnd = CreateWindowExA(
			window_ex_style, "Aether_Window_Class", m_Data.Title.c_str(),
			window_style, window_x, window_y, window_width, window_height,
			0, 0, m_hInstance, 0);

		if (m_hWnd == 0) {
			AT_FATAL("Failed to create window!");
			return;
		}

		bool shouldActivate = 1;
		int32_t showWindowCommandFlags = shouldActivate ? SW_SHOW : SW_SHOWNOACTIVATE;
		ShowWindow(m_hWnd, showWindowCommandFlags);

		m_GraphicsContext = GraphicsContext::Create((void*)m_hWnd, m_Data.Width, m_Data.Height);
		m_GraphicsContext->Init();
	}

	void Win32Window::Shutdown()
	{
		m_GraphicsContext.reset();

		DestroyWindow(m_hWnd);
		UnregisterClassA("Aether_Window_Class", m_hInstance);
	}

	LRESULT CALLBACK Message_Proc(HWND hWnd, uint32_t msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_CLOSE:
			EventManager::Emit(WindowCloseEvent());
			return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_SIZE: {
			RECT r;
			GetClientRect(hWnd, &r);
			uint32_t width = r.right - r.left;
			uint32_t height = r.bottom - r.top;
			if (width > 0 && height > 0)
				EventManager::Emit(WindowResizeEvent(width, height));
			else
			{
				EventManager::Emit(WindowMinimizeEvent(wParam == SIZE_MINIMIZED ? true : false));
				SetWindowPos(hWnd, 0, CW_USEDEFAULT, CW_USEDEFAULT, 1600, 900, SWP_NOMOVE | SWP_NOZORDER);
				ShowWindow(hWnd, SW_SHOWMINIMIZED);
			}
		} break;
		}

		return DefWindowProcA(hWnd, msg, wParam, lParam);
	}

}
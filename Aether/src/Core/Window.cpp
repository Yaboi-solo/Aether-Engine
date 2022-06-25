#include "atpch.h"
#include "Window.h"

#ifdef AT_PLATFORM_WINDOWS
#include "Platform/Win32/Win32Window.h"
#endif

namespace Aether {
	Scope<Window> Window::Create(const WindowProperties& properties)
	{
#ifdef AT_PLATFORM_WINDOWS
		return CreateScope<Win32Window>(properties);
#else
		AT_ASSERT(false, "Unknown platform!");
		return nullptr;
#endif
	}
}
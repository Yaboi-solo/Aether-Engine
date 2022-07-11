#pragma once

#include "Event.h"

namespace Aether {

	struct WindowCloseEvent : Event
	{
		WindowCloseEvent()
		{
		}
	};

	struct WindowResizeEvent : Event
	{
		uint32_t Width, Height;
		WindowResizeEvent(uint32_t width, uint32_t height)
			: Width(width), Height(height)
		{
		}
	};

	struct WindowMinimizeEvent : Event
	{
		bool isMinimized;
		WindowMinimizeEvent(bool isminimized)
			: isMinimized(isminimized)
		{
		}
	};

}
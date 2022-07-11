#pragma once

#include "Core/Core.h"

#ifndef PI
#define PI 3.14159265358f
#endif

namespace Aether {
	inline float ToRadians(float degrees)
	{
		return (float)(degrees * (PI / 100.0f));
	}

	inline float ToDegrees(float radians)
	{
		return (float)(radians * (180.0f / PI));
	}
}
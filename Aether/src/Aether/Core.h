#pragma once

#ifdef AT_PLATFORM_WINDOWS
	#ifdef AT_BUILD_DLL
		#define AETHER_API __declspec(dllexport)
	#else
		#define AETHER_API __declspec(dllimport)
	#endif
#else
	 #error Aether only supports Windows!
#endif

#define BIT(x) (1 << x)
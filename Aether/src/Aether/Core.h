#pragma once

#ifdef AT_PLATFORM_WINDOWS
#ifdef AT_DYNAMIC_LINK
	#ifdef AT_BUILD_DLL
		#define AETHER_API __declspec(dllexport)
	#else
		#define AETHER_API __declspec(dllimport)
	#endif
#else
	#define AETHER_API
#endif
#else
	 #error Aether only supports Windows!
#endif

#ifdef AT_ENABLE_ASSERTS
	#define AT_ASSERT(x, ...) {if(!(x)) { AT_ERROR("Assertion Failed : {0}", __VA_ARGS__); _debugbreak(); } }
	#define AT_CORE_ASSERT(x, ...) {if(!(x)) { AT_ERROR("Assertion Failed : {0}", __VA_ARGS__); _debugbreak(); } }
#else
	#define AT_ASSERT(x, ...)
	#define AT_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define AT_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
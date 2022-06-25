#pragma once


#ifdef _WIN32
	#ifdef _WIN64
		#define AT_PLATFORM_WINDOWS
	#else
		#error "x86 builds not supported!"
	#endif
#endif




#define AT_ENABLE_ASSERTIONS

#ifdef AT_ENABLE_ASSERTIONS

#ifdef AT_PLATFORM_WINDOWS
	#define AT_DEBUGBREAK() __debugbreak()
#endif

	#define AT_ASSERT(exp, message) \
		if (!(exp)) \
		{ \
			AT_FATAL("Assertion Failed: Line {0} ({1})", __LINE__, __FILE__); \
			AT_DEBUGBREAK(); \
		}
#else
	#define AT_ASSERT(exp, message)
#endif


#include <memory>

namespace Aether {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}
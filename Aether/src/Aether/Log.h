#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"

namespace Aether {

	class AETHER_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

//Core Log macros
#define AT_CORE_TRACE(...)  ::Aether::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define AT_CORE_INFO(...)   ::Aether::Log::GetCoreLogger()->info(__VA_ARGS__)
#define AT_CORE_WARN(...)   ::Aether::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define AT_CORE_ERROR(...)  ::Aether::Log::GetCoreLogger()->error(__VA_ARGS__)
#define AT_CORE_FATAL(...)  ::Aether::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//Client Log macros
#define AT_TRACE(...)		::Aether::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define AT_INFO(...)		::Aether::Log::GetCoreLogger()->info(__VA_ARGS__)
#define AT_WARN(...)		::Aether::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define AT_ERROR(...)		::Aether::Log::GetCoreLogger()->error(__VA_ARGS__)
#define AT_FATAL(...)		::Aether::Log::GetCoreLogger()->fatal(__VA_ARGS__)


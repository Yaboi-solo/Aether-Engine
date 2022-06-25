#pragma once

#include <format>

#define AT_ENABLE_INFO
#define AT_ENABLE_TRACE

namespace Aether {

	class Log
	{
	public:
		enum class Log_Level
		{
			Fatal = 0,
			Error = 1,
			Warn = 2,
			Info = 3,
			Trace = 4
		};
	public:
		static void Init();
		static void Shutdown();

		static void Output(Log_Level level, const std::string& message);
	};
}

#define AT_FATAL(message, ...) ::Aether::Log::Output(::Aether::Log::Log_Level::Fatal, std::format(message, __VA_ARGS__))
#define AT_ERROR(message, ...) ::Aether::Log::Output(::Aether::Log::Log_Level::Error, std::format(message, __VA_ARGS__))
#define AT_WARN(message, ...) ::Aether::Log::Output(::Aether::Log::Log_Level::Warn, std::format(message, __VA_ARGS__))

#ifdef AT_ENABLE_INFO
#define AT_INFO(message, ...) ::Aether::Log::Output(::Aether::Log::Log_Level::Info, std::format(message, __VA_ARGS__))
#else
#define AT_INFO(message, ...)
#endif

#ifdef AT_ENABLE_TRACE
#define AT_TRACE(message, ...) ::Aether::Log::Output(::Aether::Log::Log_Level::Trace, std::format(message, __VA_ARGS__))
#else
#define AT_TRACE(message, ...)
#endif
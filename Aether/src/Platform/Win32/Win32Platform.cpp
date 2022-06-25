#include "atpch.h"
#include "Core/Platform.h"

#ifdef AT_PLATFORM_WINDOWS

#include <Windows.h>

namespace Aether {

	void Aether::Platform::OutputMessage(const std::string& message, uint8_t logLevel)
	{
		uint8_t levels[] = {
			BACKGROUND_RED, // FATAL
			FOREGROUND_RED, // ERROR
			FOREGROUND_RED | FOREGROUND_GREEN, // WARN
			FOREGROUND_GREEN, // INFO
			FOREGROUND_INTENSITY // TRACE
		};

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), levels[logLevel]);
		OutputDebugStringA(message.c_str());
		uint64_t length = strlen(message.c_str());
		LPDWORD number_written = 0;
		WriteConsoleA(GetStdHandle(STD_ERROR_HANDLE), message.c_str(), (DWORD)length, number_written, 0);
	}
}

#endif
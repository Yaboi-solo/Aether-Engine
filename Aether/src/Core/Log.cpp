#include "atpch.h"
#include "Log.h"


#include "Platform.h"

namespace Aether {
	void Log::Init()
	{
		// Eventually create a log file to save to
	}

	void Log::Shutdown()
	{
		// Eventually save log content to file
	}

	void Log::Output(Log_Level level, const std::string& message)
	{

		std::string Log_Level_Str[] = { "[FATAL]: ", "[ERROR]: ", "[WARN]: ", "[INFO]: ", "[TRACE]: " };

		std::stringstream ss;
		ss << Log_Level_Str[(int)level] << message << "\n";


		Platform::OutputMessage(ss.str(), (uint8_t)level);
		
	}
}
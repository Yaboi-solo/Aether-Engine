#include "atpch.h"
#include "Log.h"


#include "Platform.h"

#include <filesystem>

namespace Aether {

	std::ofstream Log::m_File;

	void Log::Init()
	{
		std::string logFileName = "AetherLogOutput.log";

		
		if (!std::filesystem::exists(logFileName))
		{
			std::ofstream outFile(logFileName);
			outFile.close();

			m_File.open(logFileName, std::ios::trunc | std::ios::out || std::ios::in);

			AT_TRACE("Created Log file.");
		}
		else {
			m_File.open(logFileName, std::ios::trunc | std::ios::out || std::ios::in);

			AT_TRACE("Log file already exists... Erasing content.");
		}
	}

	void Log::Shutdown()
	{
		// Eventually save log content to file
		//AT_TRACE("Closed Log file.");
		//m_File.close();
		
		// Currently, closing the log file when shutting down causes the the file to no longer point
		// to an existing file
		// and due to that, any error messages that come from the Scope<Window> or its GraphicsContext
		// Are not saved to the log file
		// Hence we are not closing the file, as the application closes anyway
		// deallocating its resources
	}

	void Log::Output(Log_Level level, const std::string& message)
	{

		std::string Log_Level_Str[] = { "[FATAL]: ", "[ERROR]: ", "[WARN]: ", "[INFO]: ", "[TRACE]: " };

		std::stringstream ss;
		ss << Log_Level_Str[(int)level] << message << "\n";

		m_File << ss.str();
		Platform::OutputMessage(ss.str(), (uint8_t)level);
		
	}
}
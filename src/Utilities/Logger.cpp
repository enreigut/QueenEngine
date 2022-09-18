#include "Logger.h"

Logger::Logger()
{

}

Logger::~Logger()
{

}

const char* Logger::LevelToString(LogLevel& level)
{
	switch (level)
	{
	case LogLevel::DEBUG:
		return "DEBUG";
	case LogLevel::INFO:
		return "INFO";
	case LogLevel::WARN:
		return "WARN";
	case LogLevel::ERROR:
		return "ERROR";
	case LogLevel::SUCCESS:
		return "SUCCESS";
	default:
		return "NONE";
	}
}

void Logger::Log(LogLevel level, const char* msg)
{
	std::printf("%s (%s): %s\n", m_timer.GetFormattedTime().c_str(), LevelToString(level), msg);
}
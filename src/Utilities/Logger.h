#pragma once

#include <stdio.h>
#include "Timer.h"

enum class LogLevel
{
	DEBUG = 0,
	INFO = 1,
	WARN = 2,
	ERROR = 3,
	SUCCESS = 4
};

class Logger
{
public:
	Logger();
	~Logger();
	
	// Getters

	// Setters

	// Derived
	const char* LevelToString(LogLevel& level);
	void Log(LogLevel level, const char* msg);

private:
	Timer m_timer;
};
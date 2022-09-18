#pragma once

#include <chrono>
#include <time.h>
#include <sstream>

class Timer
{
public:
	Timer();
	~Timer();

	// Getters
	std::string GetFormattedTime() const;

	// Setters
	
	// Derived
	void Start();
	void Stop();
	void DurationInMs();

public:
	std::chrono::steady_clock::time_point p_start;
	std::chrono::steady_clock::time_point p_end;
	float p_durationInMs = 1.0f;

private:
	std::chrono::high_resolution_clock m_clock;
};
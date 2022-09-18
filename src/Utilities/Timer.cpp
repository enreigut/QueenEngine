#include "Timer.h"

Timer::Timer() 
{

}

Timer::~Timer()
{

}

std::string Timer::GetFormattedTime() const
{
	std::stringstream ss;
	time_t rawtime;
	struct tm* timeInfo;
	time(&rawtime);
	timeInfo = localtime(&rawtime);
	ss <<
		"[" <<
		timeInfo->tm_mday << "/" <<
		(timeInfo->tm_mon + 1) << "/" <<
		(timeInfo->tm_year + 1900) << " " <<
		(timeInfo->tm_hour) << ":" <<
		(timeInfo->tm_min) << ":" <<
		(timeInfo->tm_sec) << "]";
	return ss.str();
}

void Timer::Start()
{
	p_start = m_clock.now();
}

void Timer::Stop()
{
	p_end = m_clock.now();
}

void Timer::DurationInMs()
{
	p_durationInMs = (float)(p_end - p_start).count() / 1000000000;
}
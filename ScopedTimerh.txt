#pragma once
#include "pch.h"

struct ScopedTimer
{
	ScopedTimer(const char*);
	~ScopedTimer();

private:
	void Stop();
	std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
	const char* m_Name;
};


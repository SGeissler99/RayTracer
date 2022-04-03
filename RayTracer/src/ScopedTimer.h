#pragma once
#include "pch.h"

struct ScopedTimer
{
	explicit ScopedTimer(const char* name);
	~ScopedTimer();

private:
	void Stop() const;
	
	std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
	const char* m_Name;
};


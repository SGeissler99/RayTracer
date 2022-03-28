#include "pch.h"
#include "ScopedTimer.h"

ScopedTimer::ScopedTimer(const char* name) {
	m_StartTimepoint = std::chrono::high_resolution_clock::now();
	m_Name = name;
}

ScopedTimer::~ScopedTimer() {
	Stop();
}

void ScopedTimer::Stop() {
	std::chrono::time_point<std::chrono::high_resolution_clock> endTimepoint = std::chrono::high_resolution_clock::now();

	int64_t duration = std::chrono::duration_cast<std::chrono::microseconds>(endTimepoint - m_StartTimepoint).count();

	double ms = duration * 0.001;

	std::cout << m_Name << " took " << duration << "us (" << ms << "ms)\n";
}
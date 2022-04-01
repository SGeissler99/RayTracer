#include "pch.h"
#include "random.h"

static unsigned int m_Seed = 0x12345678;

unsigned int RandomInt() {
	m_Seed ^= m_Seed << 13;
	m_Seed ^= m_Seed >> 17;
	m_Seed ^= m_Seed << 5;
	return m_Seed;
}

unsigned int RandomInt(unsigned int& seed) {
	seed ^= seed << 13;
	seed ^= seed >> 17;
	seed ^= seed << 5;
	return seed;
}

float RandomFloat() {
	return (float)(RandomInt()) * 2.3283064365387e-10f;
}

float RandomFloat(unsigned int& seed) {
	return (float)(RandomInt(seed)) * 2.3283064365387e-10f;
}

float RandInRange(float range) {
	return RandomFloat() * range;
}
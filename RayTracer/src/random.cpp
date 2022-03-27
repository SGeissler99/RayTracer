#include "pch.h"
#include "random.h"

static unsigned int seed = 0x12345678;

unsigned int RandomInt() {
	seed ^= seed << 13;
	seed ^= seed >> 17;
	seed ^= seed << 5;
	return seed;
}

unsigned int RandomInt(unsigned int& seed) {
	seed ^= seed << 13;
	seed ^= seed >> 17;
	seed ^= seed << 5;
	return seed;
}

float RandomFloat() {
	return RandomInt() * 2.3283064365387e-10f;
}

float RandomFloat(unsigned int& seed) {
	return RandomInt(seed) * 2.3283064365387e-10f;
}

float RandInRange(float range) {
	return RandomFloat() * range;
}
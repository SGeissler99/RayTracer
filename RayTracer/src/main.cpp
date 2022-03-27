#include "pch.h"
#include "vector3.h"
#include "vector_math.h"

#define IMG_WIDTH 800
#define IMG_HEIGHT 800

#define AA_LEVEL 2

#define PI 3.1415926535f

std::ostream& operator<<(std::ostream& stream, const vector3& other) {
	stream << "(" << other.x << ", " << other.y << ", " << other.z << ")";
	return stream;
}

int main() {
	std::cin.get();
	
}
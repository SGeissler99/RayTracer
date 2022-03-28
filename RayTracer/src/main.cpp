#include "pch.h"
#include "vector3.h"
#include "vector_math.h"
#include "ScopedTimer.h"
#include "camera.h"
#include "image.h"

constexpr int IMG_WIDTH = 800;
constexpr int IMG_HEIGHT = 800;
constexpr int AA_LEVEL = 2;
constexpr float PI = 3.1415926535f;

std::ostream& operator<<(std::ostream& stream, const vector3& other) {
	stream << "(" << other.x << ", " << other.y << ", " << other.z << ")";
	return stream;
}

int main() {
	// TODO: Define Copy constructor for vector3
	camera cam(vector3(0, 0, 0), vector3(0, 0, 1), 1.f);
	image img(cam.get_screen_center());
	
	{
		ScopedTimer timer("Double For Loop");
		for (int x = 0; x < IMG_WIDTH; ++x) {
			for (int y = 0; y < IMG_HEIGHT; ++y) {
				vector3 pixel_color(0.f);
				vector3 ray_direction = (img.pixel_location(x, y) - cam.get_position()).normalize();
			}
		}
	}
	
	std::cin.get();
}
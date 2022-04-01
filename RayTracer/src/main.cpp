#include "pch.h"
#include "vector3.h"
#include "vector_math.h"
#include "ScopedTimer.h"
#include "camera.h"
#include "image.h"
#include "ray.h"
#include "sphere.h"
#include "light.h"

constexpr int IMG_WIDTH = 800;
constexpr int IMG_HEIGHT = 800;
constexpr int AA_LEVEL = 2;
constexpr float PI = 3.1415926535f;

std::ostream& operator<<(std::ostream& stream, const vector3& other) {
	stream << "(" << other.x << ", " << other.y << ", " << other.z << ")";
	return stream;
}

vector3 trace(const ray& r, const std::vector<sphere*>& spheres, const std::vector<light*> lights,
	const int& index, const int& depth) 
{
	vector3 ray_color(0.f);

	if (depth <= 0 || index == -1)
		return ray_color;

	vector3 intersection_point = r.get_intersection();
	vector3 normal = spheres[index]->get_normal(intersection_point);

	for (int i = 0; i < lights.size(); ++i) {

		vector3 direction_to_light = lights[i]->get_position() - intersection_point;
		float distance_to_light = direction_to_light.length();
		ray shadow_ray(intersection_point, direction_to_light);

		bool not_occluded = true;

		for (int j = 0; j < spheres.size(); ++j) {

			if (spheres[j]->intersect_ray(shadow_ray) &&
				shadow_ray.Distance < distance_to_light + spheres[j]->Epsilon) {
				not_occluded = false;
				break;
			}
		}

		if (not_occluded) {
			float angle = fmax(0.f, shadow_ray.get_direction().dot(normal));
			float diffuse = lights[i]->get_intensity() / (distance_to_light * distance_to_light) * angle;
			ray_color += vector3(1.f, 0.f, 0.f) * diffuse * lights[i]->get_color();
		}
	}

	return ray_color;
}


int main() {
	camera cam(vector3(0, 0, 0), vector3(0, 0, 1), 1);
	image img(cam.get_screen_center());

	sphere s1 = sphere(vector3(-3, 3, 14), 2);
	sphere s2 = sphere(vector3(3, 3, 11), 3);
	light l1 = light(vector3(-4, -4, 15), vector3(1), 5);
	light l2 = light(vector3(4, -4, 15), vector3(1), 5);

	std::vector<sphere*> spheres = { &s1, &s2 };
	std::vector<light*> lights = { &l1, &l2 };

	int ray_depth = 3;

	{
		ScopedTimer timer("Double For Loop");
		for (int x = 0; x < IMG_WIDTH; ++x) {
			for (int y = 0; y < IMG_HEIGHT; ++y) {
				vector3 pixel_color(0.f);

				for (int sample = 0; sample < AA_LEVEL; ++sample) {
					float u = ((float)x + RandInRange(1)) / IMG_WIDTH;
					float v = ((float)y + RandInRange(1)) / IMG_HEIGHT;

					ray r(cam.get_position(), (img.pixel_location(u, v) - cam.get_position()).normalize());

					pixel_color += trace(r, spheres, lights, r.nearest_intersection(spheres), ray_depth);
				}

				pixel_color /= AA_LEVEL;
			}
		}
	}
	
	std::cin.get();
}
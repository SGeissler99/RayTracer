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
constexpr float PI = std::numbers::pi_v<float>;

std::ostream& operator<<(std::ostream& stream, const Vector3& other) {
	stream << "(" << other.x << ", " << other.y << ", " << other.z << ")";
	return stream;
}

Vector3 Trace(const Ray& r, std::span<Sphere* const> spheres, std::span<Light* const> lights,
	const int& index, const int& depth) 
{
	Vector3 ray_color(0.f);

	if (depth <= 0 || index == -1)
		return ray_color;

	Vector3 intersection_point = r.GetIntersectionPoint();
	Vector3 normal = spheres[index]->GetNormal(intersection_point);
	
	for (const auto& l : lights) {
		Vector3 direction_to_light = l->GetPosition() - intersection_point;
		Ray shadow_ray(intersection_point, direction_to_light);
		float distance_to_light = direction_to_light.Length();

		bool not_occluded = true;

		for (const auto& s : spheres) {
			if (s->IntersectRay(shadow_ray) &&
				shadow_ray.GetDistance() < distance_to_light + s->Epsilon) {
				not_occluded = false;
				break;
			}
		}

		if (not_occluded) {
			float angle = fmax(0.f, shadow_ray.GetDirection().Dot(normal));
			float diffuse = l->GetIntensity() / (distance_to_light * distance_to_light) * angle;
			ray_color += Vector3(1.f, 0.f, 0.f) * diffuse * l->GetColor();
		}
	}

	return ray_color;
}


int main() {
	Camera cam(Vector3(0, 0, 0), Vector3(0, 0, 1), 1);
	Image img(cam.GetScreenCenter());

	Sphere s1 (Vector3(-3, 3, 14), 2);
	Sphere s2 (Vector3(3, 3, 11), 3);
	Light l1 (Vector3(-4, -4, 15), Vector3(1), 5);
	Light l2 (Vector3(4, -4, 15), Vector3(1), 5);

	const std::vector<Sphere*> spheres = { &s1, &s2 };
	const std::vector<Light*> lights = { &l1, &l2 };

	int ray_depth = 3;

	for (int x = 0; x < IMG_WIDTH; ++x) {
		for (int y = 0; y < IMG_HEIGHT; ++y) {
			Vector3 pixel_color(0.f);

			for (int sample = 0; sample < AA_LEVEL; ++sample) {
				float u = ((float)x + RandInRange(1)) / IMG_WIDTH;
				float v = ((float)y + RandInRange(1)) / IMG_HEIGHT;

				Ray r(cam.GetPosition(), (img.GetPixelLocation(u, v) - cam.GetPosition()).Normalize());

				pixel_color += Trace(r, spheres, lights, r.GetNearestIntersection(spheres), ray_depth);
			}

			pixel_color /= AA_LEVEL;
		}
	}
	
	std::cin.get();
}
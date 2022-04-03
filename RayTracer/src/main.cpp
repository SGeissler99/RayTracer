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
constexpr float VACUUM_REFRACTION = 1.0f;
constexpr float PI = std::numbers::pi_v<float>;

std::ostream& operator<<(std::ostream& stream, const Vector3& other) {
	stream << "(" << other.x << ", " << other.y << ", " << other.z << ")";
	return stream;
}

Vector3 Refract(const Vector3& direction, const Vector3& normal, float refractive) {
	float incomingAngle = direction.Dot(normal);

	float n1 = VACUUM_REFRACTION;
	float n2 = refractive;

	if (incomingAngle > 0) {
		n1 = refractive;
		n2 = VACUUM_REFRACTION;
	}

	incomingAngle = fabs(incomingAngle);
	float refractionRatio = n1 / n2;

	float kFactor = 1 - (refractionRatio * refractionRatio) * (1 - (incomingAngle * incomingAngle));
	
	return (direction * refractionRatio + normal * (refractionRatio * incomingAngle - sqrt(kFactor))).Normalize();
}

float Fresnel(const Vector3& direction, const Vector3& normal, float refractive) {

	float incomingCosineAngle = direction.Dot(normal);

	float n1 = VACUUM_REFRACTION;
	float n2 = refractive;

	if (incomingCosineAngle > 0) {
		n1 = refractive;
		n2 = VACUUM_REFRACTION;
	}

	incomingCosineAngle = fabs(incomingCosineAngle);

	float refractionRatio = n1 / n2;
	float incomingSineAngle = refractionRatio * sqrt(1 - incomingCosineAngle * incomingCosineAngle);

	if (incomingSineAngle >= 1)
		return 1;

	float transmittedAngle = sqrt(1 - incomingSineAngle * incomingSineAngle);

	float sPolarizedLight = (n1 * incomingCosineAngle - n2 * transmittedAngle) / (n1 * incomingCosineAngle + n2 * transmittedAngle);
	float pPolarizedLight = (n1 * transmittedAngle - n2 * incomingCosineAngle) / (n1 * transmittedAngle + n2 * incomingCosineAngle);

	return (sPolarizedLight * sPolarizedLight + pPolarizedLight * pPolarizedLight) / 2;
}

Vector3 Trace(const Ray& r, std::span<Sphere const> spheres, std::span<Light const> lights,
	const int& index, const int& depth) 
{
	Vector3 rayColor;

	if (depth <= 0 || index == -1)
		return rayColor;

	const Sphere& sphere = spheres[index];

	Vector3 intersectionPoint = r.GetIntersectionPoint();
	Vector3 normal = sphere.GetNormal(intersectionPoint);

	if (sphere.IsPerfectMirror()) {
		Ray reflectionRay(intersectionPoint, vectormath::Reflect(r.GetDirection(), normal));
		int closestIntersection = reflectionRay.GetNearestIntersection(spheres);

		if (closestIntersection != index) { 
			rayColor += sphere.GetReflective() * Trace(reflectionRay, spheres, lights, closestIntersection, depth - 1);
		}
	}

	if (sphere.IsDiElectric()) {
		Vector3 refractionColor;
		float fresnelFactor = Fresnel(r.GetDirection(), normal, sphere.GetRefractive());

		Vector3 reflectionColor;
		Ray reflectionRay(intersectionPoint, vectormath::Reflect(r.GetDirection(), normal));

		if (int closestIntersection = reflectionRay.GetNearestIntersection(spheres); closestIntersection != index) {
			reflectionColor = sphere.GetReflective() * Trace(reflectionRay, spheres, lights, closestIntersection, depth - 1);
		}
		
		if (fresnelFactor < 1) {
			Ray refractionRay(intersectionPoint, Refract(r.GetDirection(), normal, sphere.GetRefractive()));

			refractionColor = Trace(refractionRay, spheres, lights, refractionRay.GetNearestIntersection(spheres), depth - 1);
		}

		rayColor += reflectionColor * fresnelFactor + refractionColor * (1 - fresnelFactor);
	}

	for (const auto& l : lights) {
		Vector3 directionToLight = l.GetPosition() - intersectionPoint;
		Ray shadowRay(intersectionPoint, directionToLight);
		float distanceToLight = directionToLight.Length();

		bool isOccluded = false;

		for (const auto& s : spheres) {
			if (s.IntersectRay(shadowRay) &&
				shadowRay.GetDistance() < distanceToLight + s.Epsilon) {
				isOccluded = true;
				break;
			}
		}

		if (isOccluded) 
			continue;

		float angle = max(0, shadowRay.GetDirection().Dot(normal));
		float diffuse = l.GetIntensity() / (distanceToLight * distanceToLight) * angle;
		rayColor += sphere.GetColor() * diffuse * l.GetColor();
	}

	return rayColor;
}

int main() {
	Camera cam(Vector3(0, 0, 0), Vector3(0, 0, 1), 1);
	Image img(cam.GetScreenCenter());

	const std::array<Sphere, 2> spheres = 
	{ 
		Sphere(Vector3(-3, 3, 14), 2, 0, 0, 0),
		Sphere(Vector3(3, 3, 11), 3, 0, 0, 0) 
	};

	const std::array<Light, 2> lights = 
	{ 
		Light(Vector3(-4, -4, 15), Vector3(1), 5), 
		Light(Vector3(4, -4, 15), Vector3(1), 5)
	};

	int rayDepth = 3;

	for (int x = 0; x < IMG_WIDTH; ++x) {
		for (int y = 0; y < IMG_HEIGHT; ++y) {
			Vector3 pixelColor;

			for (int sample = 0; sample < AA_LEVEL; ++sample) {
				float u = ((float)x + RandInRange(1)) / IMG_WIDTH;
				float v = ((float)y + RandInRange(1)) / IMG_HEIGHT;

				Ray r(cam.GetPosition(), (img.GetPixelLocation(u, v) - cam.GetPosition()).Normalize());

				pixelColor += Trace(r, spheres, lights, r.GetNearestIntersection(spheres), rayDepth);
			}

			Vector3 finalColor = vectormath::Clamp(pixelColor / AA_LEVEL, 0.0f, 1.0f);
		}
	}
	
	std::cin.get();
}

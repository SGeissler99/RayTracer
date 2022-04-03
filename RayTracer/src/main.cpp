#include "pch.h"
#include "vector3.h"
#include "vector_math.h"
#include "ScopedTimer.h"
#include "camera.h"
#include "image.h"
#include "ray.h"
#include "sphere.h"
#include "light.h"

// Constants 
constexpr size_t imageWidth = 800;
constexpr size_t imageHeight = 800;
constexpr int pixelSamples = 2;
constexpr float vacuumRefraction = 1.0f;

/// <summary>
/// Calculates the refraction direction of a ray, based on its direction, 
/// the normal at the point of refraction, and the refractivity of the object the ray has hit.
/// </summary>
/// <param name="direction">The incoming direction of the ray</param>
/// <param name="normal">The outward pointing normal at the point of intersection</param>
/// <param name="refractive">The refraction index of the material the ray has hit</param>
/// <returns>The refracted direction of the ray</returns>
Vector3 Refract(const Vector3& direction, const Vector3& normal, float refractive) {
	float incomingAngle = direction.Dot(normal);

	float incomingMedium = vacuumRefraction;
	float outgoingMedium = refractive;

	// An incoming angle of more than 0 means that we hit this object from inside
	// The ray refracts from the object to the vacuum
	if (incomingAngle > 0) {
		incomingMedium = refractive;
		outgoingMedium = vacuumRefraction;
	}

	incomingAngle = fabs(incomingAngle);
	float refractionRatio = incomingMedium / outgoingMedium;

	// The k-Factor determines how much the incoming ray will be refracted
	float kFactor = 1 - (refractionRatio * refractionRatio) * (1 - (incomingAngle * incomingAngle));
	
	return (direction * refractionRatio + normal * (refractionRatio * incomingAngle - sqrt(kFactor))).Normalize();
}

/// <summary>
/// Calculates the Fresnel Coefficient based on the incoming direction of the ray,
/// the normal at the point of intersection, and the refractivity of the object the ray has hit.
/// 
/// A Fresnel Coefficient of 0.3 means that a ray has a 70% chance of being refracted by the object,
/// and thus a 30% of being reflected by the object. If the coefficient is 1, total internal reflection happens
/// </summary>
/// <param name="direction">The incoming direction of the ray</param>
/// <param name="normal">The outward pointing normal at the point of intersection</param>
/// <param name="refractive">The refraction index of the material the ray has hit</param>
/// <returns>The Fresnel Coefficient that describes which percentage of rays will refract</returns>
float Fresnel(const Vector3& direction, const Vector3& normal, float refractive) {

	float incomingCosineAngle = direction.Dot(normal);

	float incomingMedium = vacuumRefraction;
	float outgoingMedium = refractive;

	// An incoming angle of more than 0 means that we hit this object from inside
	// The ray refracts from the object to the vacuum
	if (incomingCosineAngle > 0) {
		incomingMedium = refractive;
		outgoingMedium = vacuumRefraction;
	}

	incomingCosineAngle = fabs(incomingCosineAngle);

	float refractionRatio = incomingMedium / outgoingMedium;
	float incomingSineAngle = refractionRatio * sqrt(1 - incomingCosineAngle * incomingCosineAngle);

	// If the incoming sine angle is at least 1, then only internal reflection happens, no refraction
	if (incomingSineAngle >= 1)
		return 1;

	float transmittedAngle = sqrt(1 - incomingSineAngle * incomingSineAngle);

	// Calculate reflectance of s-Polarized and p-Polarized light
	float sPolarizedLight = (incomingMedium * incomingCosineAngle - outgoingMedium * transmittedAngle) / (incomingMedium * incomingCosineAngle + outgoingMedium * transmittedAngle);
	float pPolarizedLight = (incomingMedium * transmittedAngle - outgoingMedium * incomingCosineAngle) / (incomingMedium * transmittedAngle + outgoingMedium * incomingCosineAngle);

	return (sPolarizedLight * sPolarizedLight + pPolarizedLight * pPolarizedLight) / 2;
}

/// <summary>
/// Traces a ray through the scene, which determines the color of the pixel the supplied ray passes through.
/// </summary>
/// <param name="r">A ray that passes through a pixel on the screen</param>
/// <param name="spheres">A collection of spheres in the scene</param>
/// <param name="lights">A collection of lights in the scene</param>
/// <param name="index">The index of the sphere this ray has hit or -1 if it has hit nothing</param>
/// <param name="depth">The current call depth, to prevent infinite looping</param>
/// <returns>The color of the pixel</returns>
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
		// A perfect mirror will reflect all incoming rays
		Ray reflectionRay(intersectionPoint, vectormath::Reflect(r.GetDirection(), normal));
		int closestIntersection = reflectionRay.GetNearestIntersection(spheres);

		if (closestIntersection != index) { 
			rayColor += sphere.GetReflective() * Trace(reflectionRay, spheres, lights, closestIntersection, depth - 1);
		}
	}

	if (sphere.IsDiElectric()) {
		// A dielectric refracts and reflects rays
		Vector3 reflectionColor;
		Ray reflectionRay(intersectionPoint, vectormath::Reflect(r.GetDirection(), normal));

		if (int closestIntersection = reflectionRay.GetNearestIntersection(spheres); closestIntersection != index) {
			reflectionColor = sphere.GetReflective() * Trace(reflectionRay, spheres, lights, closestIntersection, depth - 1);
		}

		Vector3 refractionColor;
		float fresnelFactor = Fresnel(r.GetDirection(), normal, sphere.GetRefractive());

		if (fresnelFactor < 1) {
			Ray refractionRay(intersectionPoint, Refract(r.GetDirection(), normal, sphere.GetRefractive()));
			refractionColor = Trace(refractionRay, spheres, lights, refractionRay.GetNearestIntersection(spheres), depth - 1);
		}

		rayColor += reflectionColor * fresnelFactor + refractionColor * (1 - fresnelFactor);
	}

	for (const Light& l : lights) {
		Vector3 directionToLight = l.GetPosition() - intersectionPoint;
		Ray shadowRay(intersectionPoint, directionToLight);
		float distanceToLight = directionToLight.Length();

		bool isOccluded = false;

		for (const Sphere& s : spheres) {
			if (s.IntersectRay(shadowRay) && shadowRay.GetDistance() < distanceToLight + s.Epsilon) {
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
	std::vector<Vector3> outputImage(imageWidth * imageHeight);

	const std::array<Sphere, 2> spheres = 
	{ 
		Sphere(Vector3(-3, 3, 14), Vector3(1, 0, 0), 2, 0, 0, 0),
		Sphere(Vector3(3, 3, 11), Vector3(0, 1, 0), 3, 0, 0, 0) 
	};

	const std::array<Light, 2> lights = 
	{ 
		Light(Vector3(-4, -4, 15), Vector3(1), 5), 
		Light(Vector3(4, -4, 15), Vector3(1), 5)
	};

	int rayDepth = 3;

	for (int y = 0; y < imageHeight; ++y) 
	{
		for (int x = 0; x < imageWidth; ++x)
		{
			Vector3 pixelColor;

			for (int sample = 0; sample < pixelSamples; ++sample) {
				float u = ((float)x + RandInRange(1)) / imageWidth;
				float v = ((float)y + RandInRange(1)) / imageHeight;

				Ray r(cam.GetPosition(), (img.GetPixelLocation(u, v) - cam.GetPosition()).Normalize());

				pixelColor += Trace(r, spheres, lights, r.GetNearestIntersection(spheres), rayDepth);
			}

			Vector3 clamped = vectormath::Clamp(pixelColor / pixelSamples, 0.0f, 1.0f);
			outputImage[x + y * imageWidth] = clamped;
		}
	}

	std::ofstream outputStream("./untitled.ppm", std::ios::out | std::ios::binary);
	outputStream << "P6\n" << imageWidth << " " << imageHeight << "\n255\n";

	for (int i = 0; i < imageWidth * imageHeight; ++i) {
		outputStream << (unsigned char)(min(float(1), outputImage[i].x) * 255)
					 << (unsigned char)(min(float(1), outputImage[i].y) * 255)
					 << (unsigned char)(min(float(1), outputImage[i].z) * 255);
	}

	outputStream.close();
	std::cin.get();
}

#include "Sphere.h"

HitData Sphere::intersectionCheck(const Ray& ray) const
{
	glm::vec3 hit;
	glm::vec3 normal;

	const glm::vec3 originToClosestPoint = ray.direction * -glm::dot(ray.direction, ray.origin);
	const glm::vec3 closestPoint = originToClosestPoint + ray.origin;
	const float distSquared = glm::dot(closestPoint, closestPoint);
	constexpr float radiusSquared = 1.0f;

	if (distSquared > radiusSquared)
		return HitData();

	const float toHit = std::sqrt(radiusSquared - distSquared);

	// Get the back face if the origin is inside the sphere, otherwise get the front face
	if (glm::dot(ray.origin, ray.origin) > radiusSquared + 0.01f) {
		hit = closestPoint - ray.direction * toHit;
	} else {
		hit = closestPoint + ray.direction * toHit;
	}

	if (glm::dot(ray.direction, hit - ray.origin) < 0.01f)
		return HitData();

	// The position is equal to the normal because it's an unit sphere
	normal = hit;

	return HitData(hit, normal, &getMaterial());
}

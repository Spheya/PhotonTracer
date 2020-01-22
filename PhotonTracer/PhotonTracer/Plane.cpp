#include "Plane.h"

namespace {
	float axisAlignedPlaneIntersection(const float origin, const float inverseDirection, const float plane) {
		return (plane - origin) * inverseDirection;
	}
}

HitData Plane::intersectionCheck(const Ray& ray) const
{
	const float dist = -ray.origin.y / ray.direction.y;
	if (dist < 0.001f)
		return HitData();

	glm::vec3 hit = ray.origin + ray.direction * dist;
	constexpr float min = -1.001f;
	constexpr float max = 1.001f;

	if (hit.x < min || hit.x > max || hit.z < min || hit.z > max)
		return HitData();

	return HitData(hit, glm::vec3(0.0f, 1.0f, 0.0f), &getMaterial());
}

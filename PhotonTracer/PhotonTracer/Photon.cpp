#include "Photon.h"

Photon::Photon(const Ray& ray, const glm::vec3& colour, double intensity) :
	_ray(ray),
	_colour(colour),
	_intensity(intensity)
{}

void Photon::bounce(const glm::vec3& position, const glm::vec3& normal)
{
	_ray.origin = position;
	_ray.direction = _ray.direction - 2.0f * normal * glm::dot(_ray.direction, normal);
}

void Photon::refract(const glm::vec3& position, const glm::vec3& normal, float eta1, float eta2)
{
	_ray.origin = position;

	const float cos1 = glm::dot(normal, _ray.direction);

	const float eta = eta1 / eta2;
	const float k = 1.0f - eta * eta * (1.0f - cos1 * cos1);

	if (k < 0.0f) {
		_ray.direction = glm::vec3(0.0f);
	} else {
		_ray.direction = eta * _ray.direction - (eta * cos1 + sqrtf(k)) * normal;
	}
}

void Photon::split(double chance, const glm::vec3& colour)
{
	assert(chance >= 0.0f);
	assert(chance <= 1.0f);

	_intensity *= chance;
	_colour *= colour * float(chance);
}

const Ray& Photon::getRay() const
{
	return _ray;
}

const glm::vec3& Photon::getColour() const
{
	return _colour;
}

double Photon::getIntensity() const
{
	return _intensity;
}

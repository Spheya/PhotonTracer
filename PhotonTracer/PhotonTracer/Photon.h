#pragma once

#include "Ray.h"

class Photon
{

public:
	Photon(const Ray& ray, const glm::vec3& colour, double intensity = 1.0f);

	void bounce(const glm::vec3& position, const glm::vec3& normal);
	void refract(const glm::vec3& position, const glm::vec3& normal, float eta1, float eta2);

	void split(double chance, const glm::vec3& colour);

	const Ray& getRay() const;
	const glm::vec3& getColour() const;
	double getIntensity() const;

private:
	Ray _ray;
	glm::vec3 _colour;
	double _intensity;
};
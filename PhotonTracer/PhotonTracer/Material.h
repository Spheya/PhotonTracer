#pragma once

#include <glm/glm.hpp>

struct Material {
	
	glm::vec3 baseColour;

	float roughness;

	Material(const glm::vec3& baseColour, float roughness) :
		baseColour(baseColour),
		roughness(roughness)
	{}

	float getLightIntensity(const glm::vec3& incoming, const glm::vec3& normal, const glm::vec3& outgoing) const;
};


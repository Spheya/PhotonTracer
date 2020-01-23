#include "Material.h"

#include <algorithm>

float Material::getLightIntensity(const glm::vec3& incoming, const glm::vec3& normal, const glm::vec3& outgoing) const {
	// TODO: Don't use lambert shading for this lol
	float dot = -glm::dot(incoming, normal);
	dot = std::clamp(dot, 0.0f, 1.0f);

	glm::vec3 reflection = glm::normalize(glm::reflect(incoming, normal));
	float SpecularFactor = glm::clamp(glm::dot(outgoing, reflection), 0.0f, 1.0f);

	return dot + SpecularFactor;
}

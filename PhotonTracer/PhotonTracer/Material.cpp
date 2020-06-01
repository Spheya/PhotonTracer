#include "Material.h"

#include <algorithm>

float Material::getLightIntensity(const glm::vec3& incoming, const glm::vec3& normal, const glm::vec3&) const {
	float incomingEnergyLoss = std::clamp(-glm::dot(incoming, normal), 0.0f, 1.0f);

	return incomingEnergyLoss;
}
#pragma once

#include <glm/glm.hpp>

#include "Material.h"

struct HitData {
	glm::vec3 position;
	glm::vec3 normal;
	const Material* material;

	HitData() : _miss(true) {}

	HitData(const glm::vec3& position, const glm::vec3& normal, const Material* material) : 
		position(position),
		normal(normal),
		material(material)
	{}

	operator bool() const { return !_miss; }

private:
	bool _miss = false;

};
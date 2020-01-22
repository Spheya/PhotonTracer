#pragma once

#include <glm/glm.hpp>

namespace Maths {

	constexpr float PI = 3.1415927410125732421875f;
	constexpr float TWO_PI = 2.0f * PI;
	constexpr float HALF_PI = 0.5f * PI;

	constexpr float RAD_TO_DEG = 180.0f / PI;
	constexpr float DEG_TO_RAD = PI / 180.0f;

	constexpr float SQRT_TWO = 1.41421356237f;
	constexpr float SQRT_HALF = 0.70710678118f;

	inline glm::vec3 randomPointOnUnitSphere() {
		float alpha = (float(rand()) / float(RAND_MAX)) * TWO_PI;
		float beta = (float(rand()) / float(RAND_MAX)) * TWO_PI;

		return glm::vec3(
			sin(beta) * cos(alpha),
			sin(beta) * sin(alpha),
			cos(beta)
		);
	}

	inline glm::vec3 randomPointInsideUnitSphere() {
		//TODO: There is an better algorithm for this
		glm::vec3 pos;

		do {
			pos = glm::vec3(
				float(rand()) / float(RAND_MAX) * 2.0f - 1.0f,
				float(rand()) / float(RAND_MAX) * 2.0f - 1.0f,
				float(rand()) / float(RAND_MAX) * 2.0f - 1.0f
			);
		} while (glm::dot(pos, pos) > 1.0f);

		return pos;
	}
}
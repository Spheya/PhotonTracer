#pragma once

#include <glm/glm.hpp>

#include "Ray.h"

class Transform {
public:
	explicit Transform(
		const glm::vec3& position = glm::vec3(0.0f),
		const glm::vec3& scale = glm::vec3(1.0f),
		const glm::vec3& rotation = glm::vec3(0.0f)
	);

	void setPosition(const glm::vec3& position);
	const glm::vec3& getPosition() const;

	void setRotation(const glm::vec3& rotation);
	const glm::vec3& getRotation() const;

	void setScale(const glm::vec3& scale);
	const glm::vec3& getScale() const;

	void move(const glm::vec3& delta);
	void rotate(const glm::vec3& delta);

	const glm::mat4& getTransformation() const;
	const glm::mat4& getInverseTransformation() const;
	const glm::mat4& getNormalTransformation() const;

	glm::vec3 toObjectSpace(const glm::vec3& position) const;
	glm::vec3 toWorldSpace(const glm::vec3& position) const;
	Ray toObjectSpace(const Ray& ray) const;
	Ray toWorldSpace(Ray ray) const;
	void toWorldSpace(glm::vec3& position, glm::vec3& normal) const;

private:
	glm::vec3 _position;
	glm::vec3 _scale;
	glm::vec3 _rotation;

	glm::mat4 _transformation;
	glm::mat4 _inverseTransformation;
	glm::mat4 _normalTransformation;

	void build();
};


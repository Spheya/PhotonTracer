#pragma once
#include "SceneObject.h"
class Sphere : public SceneObject
{
public:
	using SceneObject::SceneObject;

	HitData intersectionCheck(const Ray& ray) const override;

private:
	glm::vec3 _position;
	float _radius;
};


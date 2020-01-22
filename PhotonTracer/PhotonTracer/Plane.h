#pragma once

#include "SceneObject.h"

class Plane : public SceneObject
{
public:
	using SceneObject::SceneObject;

	HitData intersectionCheck(const Ray& ray) const override;
};


#pragma once

#include "Ray.h"
#include "HitData.h"
#include "Transform.h"
#include "Material.h"

class SceneObject {
public:
	explicit SceneObject(const Material& material, const Transform& transform = Transform());

	HitData intersects(const Ray& ray) const;

	void setTransform(const Transform& transform);
	const Transform& getTransform() const;
	Transform& getTransform();

	void setMaterial(const Material& material);
	const Material& getMaterial() const;

private:
	Material _material;
	Transform _transform;

	virtual HitData intersectionCheck(const Ray& ray) const = 0;

};


#include "SceneObject.h"

SceneObject::SceneObject(const Material& material, const Transform& transform) :
	_material(material),
	_transform(transform)
{}

HitData SceneObject::intersects(const Ray & ray) const {
	Ray intersectionRay = _transform.toObjectSpace(ray);
	HitData hit = intersectionCheck(intersectionRay);
	
	glm::vec3 normal(0.0f);
	if (hit)
		_transform.toWorldSpace(hit.position, normal);

	return hit;
}

void SceneObject::setTransform(const Transform& transform) {
	_transform = transform;
}

const Transform& SceneObject::getTransform() const {
	return _transform;
}

Transform& SceneObject::getTransform() {
	return _transform;
}

void SceneObject::setMaterial(const Material& material) {
	_material = material;
}

const Material& SceneObject::getMaterial() const {
	return _material;
}

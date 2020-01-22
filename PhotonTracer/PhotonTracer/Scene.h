#pragma once

#include <vector>
#include <memory>

#include "SceneObject.h"

class Scene
{
public:
	using iterator = std::vector<std::shared_ptr<SceneObject>>::iterator;
	using const_iterator = std::vector<std::shared_ptr<SceneObject>>::const_iterator;

	void add(std::shared_ptr<SceneObject> object);
	bool remove(std::shared_ptr<SceneObject> object);

	const Transform& getCamera() const;
	Transform& getCamera();

	HitData castRay(const Ray& ray) const;

	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;

private:
	std::vector<std::shared_ptr<SceneObject>> _objects;
	Transform _camera;
};



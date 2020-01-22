#include "Scene.h"

void Scene::add(std::shared_ptr<SceneObject> object)
{
	_objects.emplace_back(std::move(object));
}

bool Scene::remove(std::shared_ptr<SceneObject> object)
{
	auto it = std::find(_objects.begin(), _objects.end(), object);
	if (it == _objects.end())
		return false;

	_objects.erase(it);
	return true;
}

const Transform& Scene::getCamera() const {
	return _camera;
}

Transform& Scene::getCamera() {
	return _camera;
}

HitData Scene::castRay(const Ray& ray) const {
	constexpr float near = 0.0001f;

	HitData currentHit;
	float currentHitDist = FLT_MAX;
	
	for (const auto& object : _objects)
	{
		HitData temp = object->intersects(ray);
		if (temp)
		{
			float hitDist = glm::dot(temp.position - ray.origin, ray.direction);
			if (hitDist < currentHitDist && hitDist > near)
			{
				currentHit = temp;
				currentHitDist = hitDist;
			}
		}
	}

	return currentHit;
}

Scene::iterator Scene::begin()
{
	return _objects.begin();
}

Scene::iterator Scene::end()
{
	return _objects.end();
}

Scene::const_iterator Scene::begin() const
{
	return _objects.begin();
}

Scene::const_iterator Scene::end() const
{
	return _objects.end();
}

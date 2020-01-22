#include "Renderer.h"

#include <iostream>
#include <algorithm>

#include "Maths.h"

Renderer::Renderer(size_t imageWidth, size_t imageHeight) :
	_image(imageWidth, imageHeight)
{}

Scene* Renderer::getScene() const
{
	return _scene.get();
}

void Renderer::setScene(std::shared_ptr<Scene> scene)
{
	_scene = std::move(scene);
}

const Image& Renderer::getImage()
{
	return _image;
}

void Renderer::resetImage()
{
	_image.resetPixels();
}

void Renderer::castPhoton(const Photon& photon, int recursion)
{
	// TODO: have a camera class
	const float aspect = float(_image.getWidth()) / float(_image.getHeight());
	const float angle = tan(70.0f);
	constexpr float near = 0.01f;

	glm::mat4 projection(
		1.0f / (aspect * angle), 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f / angle, 0.0f, 0.0f,
		0.0f, 0.0f, (-near - 100.0f) / (0.01f - 100.0f), 1.0f,
		0.0f, 0.0f, (2.0f * near * 100.0f) / (near - 100.0f), 0.0f
	);


	// Cast a ray
	const HitData hit = _scene->castRay(photon.getRay());

	if (!hit)
		return;

	const glm::vec3 toCamera = glm::normalize(_scene->getCamera().getPosition() - hit.position);
	glm::vec4 screenPos = projection * glm::vec4(_scene->getCamera().toObjectSpace(hit.position), 1.0f);
	screenPos /= screenPos.w;

	// Draw the pixel
	if (screenPos.z >= 0.0f && screenPos.z <= 1.0f) {
		HitData depthCheck = _scene->castRay(Ray(hit.position, toCamera));
		
		if (!depthCheck || glm::dot(depthCheck.position - hit.position, toCamera) > glm::dot(_scene->getCamera().getPosition() - hit.position, toCamera)) {

			int x = int((screenPos.x * 0.5f + 0.5f) * _image.getWidth());
			int y = int((-screenPos.y * 0.5f + 0.5f) * _image.getHeight());

			if (x >= 0 && x < _image.getWidth() && y >= 0 && y < _image.getHeight()) {
				float intensity = hit.material->getLightIntensity(photon.getRay().direction, hit.normal, toCamera);

				_image.writePixelData(x, y, photon.getColour() * hit.material->baseColour * intensity, photon.getIntensity() * intensity);
			}
		}
	}

	// Reflect the photon
	if (recursion > 0) {
		glm::vec3 newDirection;
		do {
			newDirection = Maths::randomPointOnUnitSphere();
		} while (glm::dot(newDirection, hit.normal) < 0.0f);

		Photon newPhoton(Ray(hit.position, newDirection), photon.getColour(), photon.getIntensity());
		newPhoton.split(hit.material->getLightIntensity(photon.getRay().direction, hit.normal, newDirection), hit.material->baseColour);

		castPhoton(newPhoton, recursion - 1);
	}
}

glm::vec3 Renderer::castRay(const Ray& ray, int recursion) {
	HitData hit = _scene->castRay(ray);

	if (!hit)
		return glm::vec3(0.0f);

	float luminance = std::clamp(-glm::dot(ray.direction, hit.normal), 0.0f, 1.0f);

	if (recursion > 0) {
		Ray reflection(hit.position, ray.direction - 2.0f * hit.normal * glm::dot(ray.direction, hit.normal));
		return castRay(reflection, recursion - 1) + (0.5f * hit.material->baseColour) * luminance;
	}
	return hit.material->baseColour * luminance;
}

void Renderer::raytraceRender() {
	float zoom = float(_image.getHeight());

	for (int x = 0; x < _image.getWidth(); ++x) {
		for (int y = 0; y < _image.getHeight(); ++y) {
			Ray ray(glm::vec3(0.0f), glm::normalize(glm::vec3(float(x - int(_image.getWidth()) / 2), float(y - int(_image.getHeight()) / 2), zoom)));
			ray = _scene->getCamera().toWorldSpace(ray);

			glm::vec3 colour = castRay(ray, 2);

			_image.writePixelData(x, int(_image.getHeight()) - y - 1, colour, 1.0);
		}
	}
}

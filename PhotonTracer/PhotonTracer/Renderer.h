#pragma once

#include "Image.h"
#include "Scene.h"
#include "Photon.h"

class Renderer
{

public:
	Renderer(size_t imageWidth, size_t imageHeight);

	Scene* getScene() const;
	void setScene(std::shared_ptr<Scene> scene);

	const Image& getImage();
	void resetImage();

	void castPhoton(const Photon& photon, int recursion);
	glm::vec3 castRay(const Ray& ray, int recursion);

	void raytraceRender();

private:
	Image _image;
	std::shared_ptr<Scene> _scene;
};


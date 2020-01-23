#include <iostream>
#include <algorithm>

#include <SFML/Graphics.hpp>

#include "Renderer.h"
#include "Plane.h"
#include "Sphere.h"
#include "Maths.h"
#include "Transform.h"

bool updateCamera(Transform& cameraTransform) {
	constexpr float moveSpeed = 20.0f;
	constexpr float rotationSpeed = 6.0f;
	constexpr float deltaTime = 0.005f;
	bool moved = false;

	std::cout << cameraTransform.getPosition().x << " " << cameraTransform.getPosition().y << " " << cameraTransform.getPosition().z << std::endl;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		cameraTransform.move(glm::vec3(sin(cameraTransform.getRotation().y), 0.0f, cos(cameraTransform.getRotation().y)) * moveSpeed * deltaTime);
		moved = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		cameraTransform.move(glm::vec3(-cos(cameraTransform.getRotation().y), 0.0f, sin(cameraTransform.getRotation().y)) * moveSpeed * deltaTime);
		moved = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		cameraTransform.move(glm::vec3(sin(cameraTransform.getRotation().y), 0.0f, cos(cameraTransform.getRotation().y)) * -moveSpeed * deltaTime);
		moved = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		cameraTransform.move(glm::vec3(-cos(cameraTransform.getRotation().y), 0.0f, sin(cameraTransform.getRotation().y)) * -moveSpeed * deltaTime);
		moved = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
	{
		cameraTransform.move(glm::vec3(0.0f, -1.0f, 0.0f) * moveSpeed * deltaTime);
		moved = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
	{
		cameraTransform.move(glm::vec3(0.0f, 1.0f, 0.0f) * moveSpeed * deltaTime);
		moved = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		cameraTransform.rotate(glm::vec3(-1.0f, 0.0f, 0.0f) * rotationSpeed * deltaTime);
		moved = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		cameraTransform.rotate(glm::vec3(1.0f, 0.0f, 0.0f) * rotationSpeed * deltaTime);
		moved = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		cameraTransform.rotate(glm::vec3(0.0f, 1.0f, 0.0f) * rotationSpeed * deltaTime);
		moved = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		cameraTransform.rotate(glm::vec3(0.0f, -1.0f, 0.0f) * rotationSpeed * deltaTime);
		moved = true;
	}

	return moved;
}

sf::Image buildImage(const Image& image) {
	sf::Image img;

	uint8_t* pixels = new uint8_t[image.getWidth() * image.getHeight() * 4];
	for (size_t x = 0; x < image.getWidth(); ++x) {
		for (size_t y = 0; y < image.getHeight(); ++y) {
			glm::vec3 colour = image.getPixelData(x, y);

			pixels[(x + y * image.getWidth()) * 4 + 0] = uint8_t(std::clamp(colour.r, 0.0f, 1.0f) * 255.0f);
			pixels[(x + y * image.getWidth()) * 4 + 1] = uint8_t(std::clamp(colour.g, 0.0f, 1.0f) * 255.0f);
			pixels[(x + y * image.getWidth()) * 4 + 2] = uint8_t(std::clamp(colour.b, 0.0f, 1.0f) * 255.0f);
			pixels[(x + y * image.getWidth()) * 4 + 3] = 255;
		}
	}

	img.create(unsigned(image.getWidth()), unsigned(image.getHeight()), pixels);

	delete[] pixels;

	return std::move(img);
}

int main() {
	constexpr size_t w = 512, h = 512;

	std::shared_ptr<Scene> scene = std::make_shared<Scene>();
	//scene->add(std::make_unique<Plane>(Material(glm::vec3(1.0f, 0.0f, 1.0f))));
	scene->add(std::make_unique<Sphere>(
		Material(glm::vec3(1.0f, 0.5f, 1.0f)),
		Transform(glm::vec3(0.0f, -1.0f, 5.0f)))
	);
	scene->add(std::make_unique<Sphere>(
		Material(glm::vec3(1.0f, 0.5f, 0.5f)),
		Transform(glm::vec3(0.0f, 1.0f, 5.0f)))
	);
	scene->add(std::make_unique<Plane>(
		Material(glm::vec3(0.5f, 1.0f, 0.5f)),
		Transform(glm::vec3(0.0f, -1.0f, 5.0f), glm::vec3(5.0f)))
	);

	scene->getCamera().setPosition(glm::vec3(0.0f, 0.2f, 2.8f));

	Renderer renderer(w, h);
	renderer.setScene(scene);

	sf::RenderWindow window(sf::VideoMode(w, h), "phOwOn tracing");

	sf::Texture texture;
	texture.loadFromImage(buildImage(renderer.getImage()));

	sf::Sprite sprite(texture);

	while (window.isOpen()) {
		sf::Event event;

		if(window.hasFocus())
			if (updateCamera(scene->getCamera()))
				renderer.resetImage();

		for (int i = 0; i < 100000; ++i) {
			renderer.castPhoton(Photon(
				Ray(
					glm::vec3(0.0f, 3.0f, 2.0f) + Maths::randomPointOnUnitSphere() * 2.0f,
					Maths::randomPointOnUnitSphere()
				),
				glm::vec3(1.0f, 1.0, 1.0f)
			),8);
		}
		//renderer.raytraceRender();

		texture.loadFromImage(buildImage(renderer.getImage()));

		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				window.close();

		window.draw(sprite);
		window.display();
		window.clear();
	}
}
#pragma once
#include <glm/glm.hpp>

class Image
{
public:
	Image(size_t width, size_t height);
	~Image();

	void writePixelData(int x, int y, const glm::vec3& colour, double intensity);
	glm::vec3 getPixelData(size_t x, size_t y) const;
	
	void resetPixels();

	size_t getWidth() const;
	size_t getHeight() const;

private:
	struct Pixel {
		glm::vec3 colour;
		double intensity = 0.0;
		double avgIntensity = 0.0;
		long rays = 0;
	};

	Pixel* _image;

	size_t _width;
	size_t _height;

	double _totalAvgIntensity = 0.0;
	size_t _hitPixels = 0;
};


#include "Image.h"

#include <iostream>

Image::Image(size_t width, size_t height) :
	_width(width),
	_height(height)
{
	_image = new Pixel[width * height];
}

Image::~Image()
{
	delete[] _image;
}

void Image::writePixelData(int x, int y, const glm::vec3& colour, double intensity)
{
	assert(x >= 0 && x < _width);
	assert(y >= 0 && y < _height);

	Pixel& target = _image[x + y * _width];

	if (target.intensity == 0.0f && intensity != 0.0f)
		++_hitPixels;

	_totalAvgIntensity -= target.avgIntensity;

	target.intensity += intensity;
	float mix = float(intensity / target.intensity);
	target.colour = target.colour * (1.0f - mix) + colour * mix;

	++target.rays;
	target.avgIntensity = target.intensity / target.rays;

	_totalAvgIntensity += target.avgIntensity;
}

void Image::resetPixels()
{
	for (size_t i = 0; i < _width * _height; ++i)
		_image[i] = Pixel();

	_totalAvgIntensity = 0.0f;
	_hitPixels = 0;
}


size_t Image::getWidth() const
{
	return _width;
}

size_t Image::getHeight() const
{
	return _height;
}

glm::vec3 Image::getPixelData(size_t x, size_t y) const
{
	assert(x >= 0 && x < _width);
	assert(y >= 0 && y < _height);

	return _image[x + y * _width].colour * glm::vec3(0.8f) * float(_image[x + y * _width].avgIntensity * _hitPixels / _totalAvgIntensity);
}

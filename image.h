#pragma once

#include <vector>

template<class T>
struct Array2D
{
	int width, height;
	std::vector<T> pixels;

	explicit Array2D(int width = 0, int height = 0)
	{
		assert(width > 0);
		assert(height > 0);

		this->width = width;
		this->height = height;
		pixels = std::vector<T>(width*height);
	}

	const T& operator()(int x, int y) const { return pixels[index(x, y)]; }
	T& operator()(int x, int y) { return pixels[index(x, y)]; }

	int index(int x, int y)const
	{
		assert(0 <= x);
		assert(x < width);
		assert(0 <= y);
		assert(y < height);

		return y*width + x;
	}
};
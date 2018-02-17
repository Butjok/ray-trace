#pragma once

#include <stdio.h>
#include "glm/glm.hpp"
#include "image.h"
#include "utils.h"

static int byte(float a) { return static_cast<int>(255*a); }
static float finalize(float value, float gamma)
{
	return saturate(pow(value, gamma));
}

const float gamma_2_2 = 2.2f;
const float inverse_gamma_2_2 = 1.f / gamma_2_2;

inline void writeBMP(FILE* out, const Array2D<glm::vec3>& image, float gamma = inverse_gamma_2_2)
{
	auto pad = (image.width * 3) % 4 == 0 ? 0 : 4 - (image.width * 3) % 4;
	auto pitch = image.width * 3 + pad;
	auto size = 54 + pitch * image.height;
	auto ssize = pitch * image.height;

	// BMP header

	putc('B', out);
	putc('M', out);
	fwrite(&size, 4, 1, out);
	putc(0, out); putc(0, out);
	putc(0, out); putc(0, out);
	putc(54, out); putc(0, out); putc(0, out); putc(0, out);

	// DIB header
	putc(40, out); putc(0, out); putc(0, out); putc(0, out);
	fwrite(&image.width, 4, 1, out);
	fwrite(&image.height, 4, 1, out);
	putc(1, out); putc(0, out);
	putc(24, out); putc(0, out);
	putc(0, out); putc(0, out); putc(0, out); putc(0, out);
	fwrite(&ssize, 4, 1, out);
	putc(0, out); putc(0, out); putc(0, out); putc(0, out);
	putc(0, out); putc(0, out); putc(0, out); putc(0, out);
	putc(0, out); putc(0, out); putc(0, out); putc(0, out);
	putc(0, out); putc(0, out); putc(0, out); putc(0, out);

	for (auto y = 0; y < image.height; ++y)
	{
		for (auto x = 0; x < image.width; ++x)
		{
			auto color = image(x, y);

			putc(byte(finalize(color.z, gamma)), out);
			putc(byte(finalize(color.y, gamma)), out);
			putc(byte(finalize(color.x, gamma)), out);
		}
		for (auto i = 0; i < pad; ++i)
		{
			putc(0, out);
		}
	}
}


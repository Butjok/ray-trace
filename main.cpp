// ConsoleApplication6.cpp : Defines the entry point for the console application.
//

#include <vector>
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "image.h"
#include "bmp-writer.hpp"
#include <memory>
#include "light.hpp"
#include <ostream>
#include <random>

#include "sphere.h"
#include "scene.h"
#include "camera.h"
#include "lighting.h"
#include "aces.h"

glm::vec3 forward(1, 0, 0);
glm::vec3 up(0, 0, 1);

static void write(const char* filename, const Array2D<glm::vec3>& image, float gamma = inverse_gamma_2_2)
{
	FILE* out = nullptr;
	fopen_s(&out, filename, "wb");
	assert(out);
	writeBMP(out, image, gamma);
	fclose(out);
}

static glm::vec3 pack_normal(const glm::vec3& normal) { return (normal + glm::vec3(1, 1, 1)) / 2.f; }
static glm::vec3 unpack_normal(const glm::vec3& normal) { return normal * 2.0f - glm::vec3(1, 1, 1); }

int main()
{
	Scene scene;

	std::random_device random_device;
	std::mt19937 generator(random_device());
	std::uniform_real_distribution<> random_position(-100, 100);
	std::uniform_real_distribution<> random_color(0, 1);

	for (auto i = 0; i < 1000; i++)
	{
		scene.spheres.push_back(Sphere(glm::vec3(
			random_position(generator),
			random_position(generator),
			random_position(generator)),
			5,
			glm::vec4(
				random_color(generator),
				random_color(generator),
				random_color(generator),
				1)));
	}

	scene.lights.push_back(std::make_shared<DirectionalLight>(glm::vec3(1,.975f,.95f), glm::vec3(1,0, -1)));
	scene.lights.push_back(std::make_shared<AmbientLight>(glm::vec3(0, .5f, 1)/7.5f));

	Camera camera(glm::vec3(-200, 0, 0), glm::vec3(1, 0, 0));

	Array2D<int> alpha(1024, 1024);
	Array2D<glm::vec3> albedo(1024, 1024);
	Array2D<glm::vec3> position(1024, 1024);
	Array2D<glm::vec3> normal(1024, 1024);
	Array2D<const Sphere*> spheres(1024, 1024);
	for (auto y = 0; y < normal.height; y++)
	{
		for (auto x = 0; x < normal.width; x++)
		{
			auto uv = glm::vec2(
				static_cast<float>(x) / normal.width,
				static_cast<float>(y) / normal.height);

			auto ray_direction = camera.ray(uv);
			Hit hit;

			if (scene.intersect(camera.position, ray_direction, hit))
			{
				alpha(x, y) = 1;
				normal(x, y) = pack_normal(hit.normal);
				position(x, y) = hit.point;
				albedo(x, y) = hit.sphere->color;
				spheres(x, y) = hit.sphere;
			}
		}
	}

	Array2D<glm::vec3> out(1024, 1024);
	Array2D<glm::vec3> out_aces(1024, 1024);
	for (auto y = 0; y < albedo.height; y++)
	{
		for (auto x = 0; x < albedo.width; x++)
		{
			if (alpha(x, y))
			{
				glm::vec3 pixel(0, 0, 0);
				for (const auto& light : scene.lights)
				{
					auto n = unpack_normal(normal(x, y));
					pixel += light->attenuation(position(x, y), spheres(x, y), scene) *
						lambert(n, light->to_light(position(x, y), n)) *
						light->color*
						albedo(x, y);
				}
				pixel *= 2;
				out(x, y) = pixel;
				out_aces(x, y) =ACESFilm(pixel);
			}
		}
	}

	write("out/normal.bmp", normal);
	write("out/position.bmp", position);
	write("out/albedo.bmp", albedo);
	write("out/out.bmp", out);
	write("out/out_aces.bmp", out_aces);

	return 0;
}
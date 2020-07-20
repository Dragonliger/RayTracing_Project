#include "raytracing.h"
#include "primitive_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"
#include <iostream>
#include <string>
#include <cmath>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

#define CHANNEL_NUM 3

using namespace std;

color ray_color(const ray& r, const primitive& world, int depth);
uint8_t double_to_imagespace(double x);

int main(int argc, char** args) {
	// Image constants
	const auto aspect_ratio = 16.0 / 9.0;
	const int image_width = 384;
	const int image_height = static_cast<int>(image_width / aspect_ratio);
	const int samples_per_pixel = 100;
	const int max_depth = 50;

	uint8_t* image = new uint8_t[image_width * image_height * CHANNEL_NUM];

	cout << "Starting process\n";

	// World
	primitive_list world;

	auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
	auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
	auto material_left = make_shared<dielectric>(1.5);
	auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);

	world.add(make_shared<sphere>(point3(0, -100.5, -1), 100.0, material_ground));
	world.add(make_shared<sphere>(point3(0.0, 0.0, -1.0), 0.5, material_center));
	world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
	world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), -0.45, material_left));
	world.add(make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));

	// Camera
	point3 lookfrom(3, 3, 2);
	point3 lookat(0, 0, -1);
	vec3 vup(0, 1, 0);
	auto dist_to_focus = (lookfrom - lookat).magnitude();
	auto aperture = 2.0;
	camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);

	// Render
	int index = 0;
	for (int j = image_height - 1; j >= 0; --j)
	{
		cout << "\rScanlines remaining: " << j << ' ' << flush;
		for (int i = 0; i < image_width; ++i)
		{			
			color pixel_color(0,0,0);
			for (int s = 0; s < samples_per_pixel; ++s) {
				// Horizontal coordinate of the viewport
				auto u = (i + random_double()) / (image_width - 1);
				// Vertical coordinate of the viewport
				auto v = (j + random_double()) / (image_height - 1);
				// The ray goes from the origin to the current coordinates of the viewport.
				ray r = cam.get_ray(u, v);
				pixel_color += ray_color(r, world, max_depth);
			}
			// We calculate the color and write it to an image.
			auto r = pixel_color.x();
			auto g = pixel_color.y();
			auto b = pixel_color.z();
			auto scale = 1.0 / samples_per_pixel;
			r = sqrt(scale * r);
			g = sqrt(scale * g);
			b = sqrt(scale * b);
			// write the clamped value of each color component.
			image[index++] = double_to_imagespace(256 * clamp(r, 0.0, 0.999));
			image[index++] = double_to_imagespace(256 * clamp(g, 0.0, 0.999));
			image[index++] = double_to_imagespace(256 * clamp(b, 0.0, 0.999));
		}
	}

	string image_name = "Image";
	if (argc > 1)
		image_name = args[1];
	image_name.append(".bmp");
	stbi_write_bmp(image_name.c_str(), image_width, image_height, CHANNEL_NUM, image);

	delete[] image;

	cout << "\nDone.\n";

	return 0;
}

// This function finds the color of a specific ray in the scene according to a gradient.
color ray_color(const ray& r, const primitive& world, int depth) {
	hit_record rec;
	// If we've exceeded the ray bounce limit, no more light is gathered.
	if (depth <= 0)
		return color(0, 0, 0);
	// Check if we hit a sphere and where.
	if (world.hit(r, 0.001, infinity, rec)) {
		ray scattered;
		color attenuation;
		if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
			return attenuation * ray_color(scattered, world, depth - 1);
		return color(0, 0, 0);
	}
	// This gets the direction of the vector in a unitary format.
	vec3 unit_direction = unit_vector(r.direction());
	// Gets the target position of the linear gradient blend only vertically.
	auto t = 0.5 * (unit_direction.y() + 1.0);
	// Returns a value in a color gradient from white(1,1,1) to blue(0.5,0.7,1.0).
	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}


// This function translates a color from double to a uint8 value compatible with stb
uint8_t double_to_imagespace(double x) {
	return static_cast<int>(x);
}
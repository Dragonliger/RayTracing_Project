#include <iostream>
#include <string>
#include <cmath>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"
#include "color.h"
#include "vec3.h"
#include "Ray.h"

#define CHANNEL_NUM 3

using namespace std;

color ray_color(const ray& r);
uint8_t double_to_imagespace(double x);
bool hit_sphere(const point3& center, double radius, const ray& r);

int main(int argc, char** args) {
	const auto aspect_ratio = 16.0 / 9.0;
	const int image_width = 384;
	const int image_height = static_cast<int>(image_width / aspect_ratio);

	uint8_t* image = new uint8_t[image_width * image_height * CHANNEL_NUM];

	cout << "Starting process\n";

	auto viewport_height = 2.0;
	auto viewport_width = aspect_ratio * viewport_height;
	auto focal_length = 1.0;

	// Where is the camera located.
	auto origin = point3(0, 0, 0);
	// Horizontal length of the viewport
	auto horizontal = vec3(viewport_width, 0, 0);
	// Vertical height of the viewport
	auto vertical = vec3(0, viewport_height, 0);
	// Origin for the screen is defined as the lower left corner.
	auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

	int index = 0;
	for (int j = image_height - 1; j >= 0; --j)
	{
		cout << "\rScanlines remaining: " << j << ' ' << flush;
		for (int i = 0; i < image_width; ++i)
		{
			// Horizontal coordinate of the viewport
			auto u = double(i) / (image_width - 1);
			// Vertical coordinate of the viewport
			auto v = double(j) / (image_height - 1);
			// The ray goes from the origin to the current coordinates of the viewport.
			ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
			// We calculate the color and write it to an image.
			color pixel_color = ray_color(r);
			image[index++] = double_to_imagespace(pixel_color.x());
			image[index++] = double_to_imagespace(pixel_color.y());
			image[index++] = double_to_imagespace(pixel_color.z());
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
color ray_color(const ray& r) {
	if (hit_sphere(point3(0, 0, -1), 0.5, r))
		return color(1, 0, 0);
	// This gets the direction of the vector in a unitary format.
	vec3 unit_direction = unit_vector(r.direction());
	// Gets the target position of the linear gradient blend only vertically.
	auto t = 0.5 * (unit_direction.y() + 1.0);
	// Returns a value in a color gradient from white(1,1,1) to blue(0.5,0.7,1.0).
	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}


// This function translates a color from double to a uint8 value compatible with stb
uint8_t double_to_imagespace(double x) {
	return (int)round(x * 255);
}

bool hit_sphere(const point3& center, double radius, const ray& r) {
	vec3 oc = r.origin() - center;
	auto a = dot(r.direction(), r.direction());
	auto b = 2.0 * dot(oc, r.direction());
	auto c = dot(oc, oc) - radius * radius;
	auto discriminant = b * b - 4 * a * c;
	return (discriminant > 0);
}
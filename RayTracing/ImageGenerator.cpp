#include <iostream>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"
#include "color.h"
#include "vec3.h"

#define CHANNEL_NUM 3

using namespace std;

int main(int argc, char** args) {
	const int image_width = 256;
	const int image_height = 256;

	uint8_t* image = new uint8_t[image_width * image_height * CHANNEL_NUM];

	cout << "Starting process\n";

	int index = 0;
	for (int j = image_height - 1; j >= 0; --j)
	{
		cout << "\rScanlines remaining: " << j << ' ' << flush;
		for (int i = 0; i < image_width; ++i)
		{
			color pixel_color(double(i) / (image_width - 1), double(j) / (image_height - 1), 0.25);
			pixel_color *= 255.99;
			image[index++] = pixel_color.x();
			image[index++] = pixel_color.y();
			image[index++] = pixel_color.z();
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
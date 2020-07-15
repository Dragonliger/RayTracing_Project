#pragma once

#include "vec3.h"

#include <iostream>

// Prints out the color
void write_color(std::ostream& out, color pixel_color) {
	// Write the translated [0,255] value of each coolor component.
	out << static_cast<int>(255.999 * pixel_color.x()) << ' '
		<< static_cast<int>(255.999 * pixel_color.y()) << ' '
		<< static_cast<int>(255.999 * pixel_color.z()) << '\n';
}
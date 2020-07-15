#pragma once

#include "vec3.h"

class ray {
// Functions
public:
	ray() {}
	ray(const point3& origin, const vec3& direction)
		: orig(origin), dir(direction)
	{}

// Members
public:
	point3 orig;
	vec3 dir;
};
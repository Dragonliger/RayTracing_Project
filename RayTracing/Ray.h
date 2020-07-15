#pragma once

#include "vec3.h"

class ray {
// Functions
public:
	ray() {}
	ray(const point3& origin, const vec3& direction)
		: orig(origin), dir(direction)
	{}

	point3 origin() const { return orig; }
	vec3 direction() const { return dir; }

	// Function P(t) =  A + tB
	// it helps simulate the movement of the ray on the scene.
	point3 at(double t) const {
		return orig + t * dir;
	}

// Members
public:
	point3 orig;
	vec3 dir;
};
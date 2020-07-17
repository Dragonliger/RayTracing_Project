#pragma once

#include "primitive.h"
#include "vec3.h"

class sphere : public primitive {
// Functions and methods
public:
	sphere() {}
	sphere(point3 cen, double r) : center(cen), radius(r) {};
	virtual bool hit(const ray& r, double tmin, double tmax, hit_record& rec) const;

// Member variables
public:
	point3 center;
	double radius;
};

bool sphere::hit(const ray& r, double tmin, double tmax, hit_record& rec) const {
	// distance from the ray origin to the center of the sphere.
	vec3 oc = r.origin() - center;
	// Magnitude of the ray minus the square radius x^2 + y^2 + z^2 = r^2
	auto a = r.direction().magnitude_squared() - radius * radius;
	auto half_b = dot(oc, r.direction());
	auto c = oc.magnitude_squared() - radius * radius;
	auto discriminant = half_b * half_b - a * c;

	// If the discriminant is positive there can be a square root otherwise
	// it is impossible.
	if (discriminant > 0) {
		auto root = sqrt(discriminant);
		auto temp = (-half_b - root) / a;
		if (temp < tmax && temp >tmin) {
			rec.t = temp;
			rec.p = r.at(rec.t);
			rec.normal = (rec.p - center) / radius;
			return true;
		}
		temp = (-half_b + root) / a;
		if (temp < tmax && temp > tmin) {
			rec.t = temp;
			rec.p = r.at(rec.t);
			rec.normal = (rec.p - center) / radius;
			return true;
		}
	}
	return false;
}
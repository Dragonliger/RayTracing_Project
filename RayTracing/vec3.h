#pragma once

#include <cmath>
#include <iostream>

using std::sqrt;

class vec3 {
// Functions
public:
	// Constructors
	vec3() : e{0,0,0} {}
	vec3(double e0, double e1, double e2) : e{ e0,e1,e2 } {}

	// Functions that return the coordinates
	double x() const { return e[0]; }
	double y() const { return e[1]; }
	double z() const { return e[2]; }

	// Operator interactions

	// Negative
	vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }

	// Accessing members from pointer
	double operator[](int i) const { return e[i]; }

	// Accessing members
	double& operator[](int i) { return e[i]; }

	// Adding a vector to this one
	vec3& operator+=(const vec3& v) {
		e[0] += v.e[0];
		e[1] += v.e[1];
		e[2] += v.e[2];
		return *this;
	}

	// Self-Multiplying by scalar
	vec3& operator*=(const double t) {
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
		return *this;
	}

	// Self-Dividing by scalar
	vec3& operator/=(const double t) {
		return *this *= 1 / t;
	}

	// Return the magnitude
	double magnitude() const {
		return sqrt(magnitude_squared());
	}
	double magnitude_squared() const {
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}

	inline static vec3 random() {
		return vec3(random_double(), random_double(), random_double());
	}

	inline static vec3 random(double min, double max) {
		return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
	}

// Variables
public:
	double e[3];
};

// Type aliases for vec3
// Only for organization purposes.
using point3 = vec3; // Spatial 3D point
using color = vec3;  // RGB color

// vec3 Utility Functions
// Print out the value
inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
	return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

// Adding two vectors together.
inline vec3 operator+(const vec3& u, const vec3& v) {
	return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

// Substracting two vectors together.
inline vec3 operator-(const vec3& u, const vec3& v) {
	return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

// Elementwise multiplication of vectors
inline vec3 operator*(const vec3& u, const vec3& v) {
	return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

// Multiplication by a scalar
inline vec3 operator*(double t, const vec3& v) {
	return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

// Multiplying an scalar by a vector
inline vec3 operator*(const vec3& v, double t) {
	return t * v;
}

// Dividing the vector by a scalar
inline vec3 operator/(vec3 v, double t) {
	return (1 / t) * v;
}

// Getting the dot product of two vectors
inline double dot(const vec3& u, const vec3& v) {
	return u.e[0] * v.e[0]
		 + u.e[1] * v.e[1]
		 + u.e[2] * v.e[2];
}

// Getting the cross product of two vectors
inline vec3 cross(const vec3& u, const vec3& v) {
	return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
				u.e[2] * v.e[0] - u.e[0] * v.e[2],
				u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

// Getting the unitary value of the vector
inline vec3 unit_vector(vec3 v) {
	return v / v.magnitude();
}

vec3 random_in_unit_sphere() {
	while (true) {
		auto p = vec3::random(-1, 1);
		if (p.magnitude_squared() >= 1) continue;
		return p;
	}
}

vec3 random_unit_vector() {
	auto a = random_double(0, 2 * pi);
	auto z = random_double(-1, 1);
	auto r = sqrt(1 - z * z);
	return vec3(r * cos(a), r * sin(a), z);
}

vec3 reflect(const vec3& v, const vec3& n) {
	return v - 2 * dot(v, n) * n;
}
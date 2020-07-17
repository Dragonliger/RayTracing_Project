#pragma once

#include "primitive.h"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class primitive_list : public primitive {
// Functions and methods
public:
	primitive_list() {}
	primitive_list(shared_ptr<primitive> object) { add(object); }
	void clear() { objects.clear(); }
	void add(shared_ptr<primitive> object) { objects.push_back(object); }
	virtual bool hit(const ray& r, double tmin, double tmax, hit_record& rec) const;

// Member variables
public:
	std::vector<shared_ptr<primitive>> objects;
};

bool primitive_list::hit(const ray& r, double tmin, double tmax, hit_record& rec) const {
	hit_record temp_rec;
	bool hit_anything = false;
	auto closest_so_far = tmax;

	for (const auto& object : objects) {
		if (object->hit(r, tmin, closest_so_far, temp_rec)) {
			hit_anything = true;
			closest_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}

	return hit_anything;
}
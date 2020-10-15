#ifndef H_VISIBLE
#define H_VISIBLE

#include "ray.h"

struct collision {
	double dist;
	vec3 point;
	vec3 normal;
};

class visible {
public:
	virtual bool intersects(const ray& r, double dist_min, double dist_max, collision& data) const = 0;
};

#endif

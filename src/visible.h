#ifndef H_VISIBLE
#define H_VISIBLE

#include "ray.h"

struct collision {
	float dist;
	vec3 point;
	vec3 normal;
};

class visible {
public:
	virtual bool intersects(const ray& r, float dist_min, float dist_max, collision& data) const = 0;
};

#endif

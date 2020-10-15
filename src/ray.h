#ifndef H_RAY
#define H_RAY

#include "vec3.h"

struct ray {
	vec3 pos, dir;

	ray() : pos(vec3()), dir(vec3()) { }
	ray(const vec3& pos, const vec3& dir) : pos(pos), dir(normalize(dir)) { }

	vec3 extend(float t) const { return pos + (dir * t); }
};

#endif

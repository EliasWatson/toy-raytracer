#ifndef H_UTIL
#define H_UTIL

#include "vec3.h"

#include <random>

template <typename T>
inline T mix(T a, T b, float n) {
	return ((1.0 - n) * a) + (n * b);
}

vec3 random_in_unit_sphere() {
	vec3 p(1.0);
	while(dot(p,p) >= 1.0) {
		p = 2.0 * vec3(drand48(), drand48(), drand48()) - vec3(1.0);
	}
	return p;
}

#endif

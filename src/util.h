#ifndef H_UTIL
#define H_UTIL

#include "vec3.h"

template <typename T>
inline T mix(T a, T b, float n) {
	return ((1.0 - n) * a) + (n * b);
}

#endif

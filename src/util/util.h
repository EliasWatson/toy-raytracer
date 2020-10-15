#ifndef H_UTIL
#define H_UTIL

#include "vec3.h"

#include <math.h>
#include <random>

template <typename T>
inline T mix(T a, T b, double n) {
	return ((1.0 - n) * a) + (n * b);
}

template <typename T>
inline T clamp(T min, T max, T val) {
	if(val < min) return min;
	if(val > max) return max;
	return val;
}

template <typename T>
inline T step(T threshold, T val) {
	if(val < threshold) return (T) 0;
	else return (T) 1;
}

inline vec3 reflect(const vec3& v, const vec3& n) {
	return v - 2.0*dot(v,n)*n;
}

bool refract(const vec3& v, const vec3& n, double ni_over_nt, vec3& refracted) {
	vec3 uv = normalize(v);
	double dt = dot(uv, n);
	double discriminant = 1.0 - ni_over_nt*ni_over_nt*(1.0 - dt*dt);
	if(discriminant > 0.0) {
		refracted = ni_over_nt*(v - n*dt) - n*sqrt(discriminant);
		return true;
	} else {
		return false;
	}
}

inline vec3 random_in_unit_sphere() {
	vec3 p(1.0);
	while(dot(p,p) >= 1.0) {
		p = 2.0 * vec3(drand48(), drand48(), drand48()) - vec3(1.0);
	}
	return p;
}

#endif

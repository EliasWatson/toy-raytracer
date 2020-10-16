#ifndef H_UTIL
#define H_UTIL

#include "vec3.h"

#include <cmath>
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

inline vec3 refract(const vec3& v, const vec3& n, double ni_over_nt) {
	double cos_theta = dot(-v, n);
	if(cos_theta > 1.0) cos_theta = 1.0;

	vec3 r_out_perp = ni_over_nt * (v + cos_theta*n);
	vec3 r_out_parallel = -sqrt(fabs(1.0 - dot(r_out_perp, r_out_perp))) * n;

	return normalize(r_out_perp + r_out_parallel);
}

inline double schlick(double cosine, double ref_idx) {
	double r0 = (1.0 - ref_idx) / (1.0 + ref_idx);
	r0 *= r0;
	return r0 + (1.0 - r0)*pow((1.0 - cosine), 5.0);
}

inline vec3 random_in_unit_sphere() {
	while(true) {
		vec3 p = (2.0 * vec3(drand48(), drand48(), drand48())) - vec3(1.0);
		if(dot(p, p) < 1.0) return p;
	}
}

#endif

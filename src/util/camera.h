#ifndef H_CAMERA
#define H_CAMERA

#include "ray.h"

struct camera {
	vec3 pos;
	vec3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;

	camera() {
		pos = vec3(0.0, 0.0, 1.0);
		lower_left_corner = vec3(-2.0, -1.0, -1.0);
		horizontal = vec3(4.0, 0.0, 0.0);
		vertical = vec3(0.0, 2.0, 0.0);
	}

	ray get_ray(double u, double v) {
		return ray(
			pos,
			lower_left_corner + u*horizontal + v*vertical - pos
		);
	}
};

#endif

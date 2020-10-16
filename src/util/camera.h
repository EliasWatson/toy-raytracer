#ifndef H_CAMERA
#define H_CAMERA

#include "ray.h"

struct camera {
	vec3 pos;
	vec3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;

	camera(vec3 pos, vec3 look_at, vec3 v_up, double v_fov, double aspect) : pos(pos) {
		double theta = v_fov * M_PI / 180.0;
		double half_height = tan(theta / 2.0);
		double half_width = aspect * half_height;

		vec3 w = normalize(pos - look_at);
		vec3 u = normalize(cross(v_up, w));
		vec3 v = cross(w, u);

		lower_left_corner = vec3(-half_width, -half_height, -1.0);
		lower_left_corner = pos - half_width*u - half_height*v - w;
		horizontal = 2.0 * half_width * u;
		vertical = 2.0 * half_height * v;
	}

	ray get_ray(double u, double v) {
		return ray(
			pos,
			lower_left_corner + u*horizontal + v*vertical - pos
		);
	}
};

#endif

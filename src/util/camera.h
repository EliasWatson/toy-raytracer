#ifndef H_CAMERA
#define H_CAMERA

#include "ray.h"
#include "util.h"

struct camera {
	vec3 pos;
	vec3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
	double lens_radius;

	camera(vec3 pos, vec3 look_at, vec3 v_up, double v_fov, double aspect, double aperture, double focus_dist) : pos(pos) {
		lens_radius = aperture / 2.0;

		double theta = v_fov * M_PI / 180.0;
		double half_height = tan(theta / 2.0);
		double half_width = aspect * half_height;

		vec3 w = normalize(pos - look_at);
		vec3 u = normalize(cross(v_up, w));
		vec3 v = cross(w, u);

		lower_left_corner = pos - half_width*focus_dist*u - half_height*focus_dist*v - focus_dist*w;
		horizontal = 2.0 * half_width * focus_dist * u;
		vertical = 2.0 * half_height * focus_dist * v;
	}

	ray get_ray(double u, double v) {
		vec3 rd = lens_radius * random_in_unit_disk();
		vec3 offset = u * rd.x + v * rd.y;
		return ray(
			pos + offset,
			lower_left_corner + u*horizontal + v*vertical - pos - offset
		);
	}
};

#endif

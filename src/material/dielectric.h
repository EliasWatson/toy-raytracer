#ifndef H_DIELECTRIC
#define H_DIELECTRIC

#include "material.h"
#include "../util/util.h"

class dielectric: public material {
public:
	double ref_idx;

	dielectric(double ri) : ref_idx(ri) { }

	virtual bool scatter(const ray& r, const collision& hit, vec3& attenuation, ray& out_ray) const {
		attenuation = vec3(1.0, 1.0, 1.0);
		double refraction_ratio = hit.front_face ? (1.0 / ref_idx) : ref_idx;

		double cos_theta = dot(-r.dir, hit.normal);
		if(cos_theta > 1.0) cos_theta = 1.0;

		double sin_theta = sqrt(1.0 - cos_theta*cos_theta);

		bool cannot_refract = refraction_ratio * sin_theta > 1.0;
		vec3 direction;

		if(cannot_refract || schlick(cos_theta, refraction_ratio) > drand48()) {
			direction = reflect(r.dir, hit.normal);
		} else {
			direction = refract(r.dir, hit.normal, refraction_ratio);
		}

		out_ray = ray(hit.point, direction);
		return true;
	}
};

#endif

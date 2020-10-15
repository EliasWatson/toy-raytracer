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
		vec3 outward_normal;
		double ni_over_nt;
		double reflect_prob;
		double cosine;

		vec3 reflected = reflect(r.dir, hit.normal);
		vec3 refracted;

		if(dot(r.dir, hit.normal) > 0.0) {
			outward_normal = -hit.normal;
			ni_over_nt = ref_idx;
			cosine = ref_idx * dot(r.dir, hit.normal);
		} else {
			outward_normal = hit.normal;
			ni_over_nt = 1.0 / ref_idx;
			cosine = -dot(r.dir, hit.normal);
		}

		if(refract(r.dir, outward_normal, ni_over_nt, refracted)) {
			reflect_prob = schlick(cosine, ref_idx);
		} else {
			reflect_prob = 1.0;
		}

		if(drand48() < reflect_prob) {
			out_ray = ray(hit.point, reflected);
		} else {
			out_ray = ray(hit.point, refracted);
		}

		return true;
	}
};

#endif

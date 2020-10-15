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

		vec3 reflected = reflect(r.dir, hit.normal);
		vec3 refracted;

		if(dot(r.dir, hit.normal) > 0.0) {
			outward_normal = -hit.normal;
			ni_over_nt = ref_idx;
		} else {
			outward_normal = hit.normal;
			ni_over_nt = 1.0 / ref_idx;
		}

		if(refract(r.dir, outward_normal, ni_over_nt, refracted)) {
			out_ray = ray(hit.point, refracted);
		} else {
			out_ray = ray(hit.point, reflected);
		}

		return true;
	}
};

#endif

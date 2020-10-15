#ifndef H_LAMBERTIAN
#define H_LAMBERTIAN

#include "material.h"
#include "../util/util.h"

class lambertian: public material {
public:
	vec3 albedo;

	lambertian() : albedo(vec3(0.5)) { }
	lambertian(const vec3& albedo) : albedo(albedo) { }

	virtual bool scatter(const ray& r, const collision& hit, vec3& attenuation, ray& out_ray) const {
		vec3 target = hit.point + hit.normal + random_in_unit_sphere();
		out_ray = ray(hit.point, target - hit.point);
		attenuation = albedo;
		return true;
	}
};

#endif

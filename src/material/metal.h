#ifndef H_METAL
#define H_METAL

#include "material.h"
#include "../util/util.h"

class metal: public material {
public:
	vec3 albedo;
	double roughness;

	metal() : albedo(vec3(0.9)), roughness(0.0) { }
	metal(const vec3& albedo, double roughness) : albedo(albedo), roughness(roughness) { }

	virtual bool scatter(const ray& r, const collision& hit, vec3& attenuation, ray& out_ray) const {
		vec3 reflected = reflect(normalize(r.dir), hit.normal);
		out_ray = ray(hit.point, reflected + roughness*random_in_unit_sphere());
		attenuation = albedo;
		return dot(out_ray.dir, hit.normal) > 0;
	}
};

#endif

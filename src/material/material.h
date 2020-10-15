#ifndef H_MATERIAL
#define H_MATERIAL

#include "../util/ray.h"
#include "../object/visible.h"

class material {
public:
	virtual bool scatter(const ray& r, const collision& hit, vec3& attenuation, ray& out_ray) const = 0;
};

#endif

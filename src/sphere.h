#ifndef H_SPHERE
#define H_SPHERE

#include "visible.h"

class sphere: public visible {
public:
	vec3 pos;
	float radius;

	sphere() { }
	sphere(vec3 pos, float radius): pos(pos), radius(radius) { }

	virtual bool intersects(const ray& r, float dist_min, float dist_max, collision& data) const;
};

bool sphere::intersects(const ray& r, float dist_min, float dist_max, collision& data) const {
	vec3 oc = r.pos - pos;
	float a = dot(r.dir, r.dir);
	float b = dot(oc, r.dir);
	float c = dot(oc, oc) - radius*radius;
	float discriminant = b*b - a*c;

	if(discriminant > 0.0) {
		float temp = (-b - sqrt(discriminant)) / a;

		for(int i = 0; i < 2; ++i) {
			if(dist_min < temp && temp < dist_max) {
				data.dist = temp;
				data.point = r.extend(temp);
				data.normal = normalize((data.point - pos) / radius);
				return true;
			}
			temp = (-b + sqrt(discriminant)) / a;
		}
	}

	return false;
}

#endif

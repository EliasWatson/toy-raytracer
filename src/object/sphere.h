#ifndef H_SPHERE
#define H_SPHERE

#include "visible.h"

class sphere: public visible {
public:
	vec3 pos;
	double radius;
	material* mat;

	sphere() { }
	sphere(vec3 pos, double radius, material* mat): pos(pos), radius(radius), mat(mat) { }

	virtual bool intersects(const ray& r, double dist_min, double dist_max, collision& data) const;
};

bool sphere::intersects(const ray& r, double dist_min, double dist_max, collision& data) const {
	vec3 oc = r.pos - pos;
	double a = dot(r.dir, r.dir);
	double b = dot(oc, r.dir);
	double c = dot(oc, oc) - radius*radius;
	double discriminant = b*b - a*c;

	if(discriminant > 0.0) {
		double temp = (-b - sqrt(discriminant)) / a;

		for(int i = 0; i < 2; ++i) {
			if(dist_min < temp && temp < dist_max) {
				data.dist = temp;
				data.point = r.extend(temp);
				data.normal = normalize((data.point - pos) / radius);
				data.mat = mat;
				return true;
			}
			temp = (-b + sqrt(discriminant)) / a;
		}
	}

	return false;
}

#endif

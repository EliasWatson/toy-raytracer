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

	virtual bool intersects(const ray& r, double dist_min, double dist_max, collision& data) const {
		vec3 oc = r.pos - pos;
		double a = dot(r.dir, r.dir);
		double half_b = dot(oc, r.dir);
		double c = dot(oc, oc) - radius*radius;
		double discriminant = half_b*half_b - a*c;

		if(discriminant > 0.0) {
			double root = sqrt(discriminant);
			double temp = (-half_b - root) / a;

			if(dist_min < temp && temp < dist_max) {
				data.dist = temp;
				data.point = r.extend(temp);
				data.normal = normalize((data.point - pos) / radius);
				data.front_face = true;
				data.mat = mat;
				return true;
			}

			temp = (-half_b + root) / a;
			if(dist_min < temp && temp < dist_max) {
				data.dist = temp;
				data.point = r.extend(temp);
				data.normal = normalize((data.point - pos) / radius);
				data.front_face = false;
				data.mat = mat;
				return true;
			}
		}

		return false;
	}
};

#endif

#include "image.h"
#include "vec3.h"
#include "ray.h"
#include "util.h"

vec3 sky_color(const ray& r) {
	float t = 0.5 * (r.dir.y + 1.0);
	return mix(vec3(1.0), vec3(0.5, 0.7, 1.0), t);
}

float hit_sphere(const vec3& center, float radius, const ray& r) {
	vec3 oc = r.pos - center;
	float a = dot(r.dir, r.dir);
	float b = 2.0 * dot(oc, r.dir);
	float c = dot(oc, oc) - radius*radius;
	float discriminant = b*b - 4.0*a*c;

	if(discriminant < 0) return -1.0;
	else return (-b - sqrt(discriminant)) / (2.0 * a);
}

void render(image* img) {
	vec3 lower_left_corner(-2.0, -1.0, -1.0);
	vec3 horizontal(4.0, 0.0, 0.0);
	vec3 vertical(0.0, 2.0, 0.0);
	vec3 origin(0.0);

	for(int y = 0; y < img->height; ++y) {
		for(int x = 0; x < img->width; ++x) {
			float u = float(x) / float(img->width);
			float v = float(y) / float(img->height);

			ray r(origin, lower_left_corner + u*horizontal + v*vertical);
			float dist = hit_sphere(vec3(0.0, 0.0, -1.0), 0.5, r);

			vec3 col;
			if(dist > 0.0) {
				vec3 nml = normalize(r.extend(dist) - vec3(0.0, 0.0, -1.0));
				col = 0.5 * vec3(nml.x + 1.0, nml.y + 1.0, nml.z + 1.0);
			} else {
				col = sky_color(r);
			}

			img->set_pixel(x, img->height - y - 1, col);
		}
	}
}

int main() {
	const int width = 800;
	const int height = 400;

	image img(width, height);
	render(&img);
	img.save("test.ppm");
}

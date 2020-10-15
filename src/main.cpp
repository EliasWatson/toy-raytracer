#include "image.h"
#include "vec3.h"
#include "ray.h"
#include "util.h"
#include "visible_list.h"
#include "sphere.h"
#include "camera.h"

#include "float.h"
#include <random>

vec3 sky_color(const ray& r) {
	float t = 0.5 * (r.dir.y + 1.0);
	return mix(vec3(1.0), vec3(0.5, 0.7, 1.0), t);
}

vec3 get_pixel(const ray& r, visible_list& world) {
	collision hit;
	if(world.intersects(r, 0.0, MAXFLOAT, hit)) {
		vec3 target = hit.point + hit.normal + random_in_unit_sphere();
		return 0.5 * get_pixel(ray(hit.point, target - hit.point), world);
	} else {
		return sky_color(r);
	}
}

void render(image* img, int samples) {
	camera cam;

	std::vector<visible*> obj_list;
	obj_list.push_back(new sphere(vec3(0.0, 0.0, -1.0), 0.5));
	obj_list.push_back(new sphere(vec3(0.0, -100.5, -1.0), 100));

	visible_list objects(obj_list);

	for(int y = 0; y < img->height; ++y) {
		for(int x = 0; x < img->width; ++x) {
			vec3 col;

			for(int i = 0; i < samples; ++i) {
				float u = float(x + drand48()) / float(img->width);
				float v = float(y + drand48()) / float(img->height);
				ray r = cam.get_ray(u, v);
				col += get_pixel(r, objects);
			}

			col /= float(samples);
			col = vec3(sqrt(col.x), sqrt(col.y), sqrt(col.z));

			img->set_pixel(x, img->height - y - 1, col);
		}
	}
}

int main() {
	const int width = 800;
	const int height = 400;
	const int samples = 128;

	image img(width, height);
	render(&img, samples);
	img.save("test.ppm");
}

#include "util/image.h"
#include "util/vec3.h"
#include "util/ray.h"
#include "util/util.h"
#include "util/camera.h"

#include "object/visible_list.h"
#include "object/sphere.h"

#include "material/lambertian.h"
#include "material/metal.h"
#include "material/dielectric.h"

#include "float.h"
#include <random>
#include <iostream>

vec3 sky_color(const ray& r) {
	double t = 0.5 * (r.dir.y + 1.0);
	return mix(vec3(1.0), vec3(0.5, 0.7, 1.0), t);
}

vec3 get_pixel(const ray& r, visible_list& world, int depth = 0) {
	if(depth > 64) return vec3(0.0);
	
	collision hit;
	if(world.intersects(r, 0.0, MAXFLOAT, hit)) {
		ray new_ray;
		vec3 attenuation;
		if(hit.mat->scatter(r, hit, attenuation, new_ray)) {
			return attenuation * get_pixel(new_ray, world, depth + 1);
		} else {
			return vec3(0.0);
		}
	} else {
		return sky_color(r);
	}
}

void render(image* img, int samples) {
	camera cam;

	std::vector<visible*> obj_list;

	// Red diffuse
	obj_list.push_back(new sphere(
		vec3(0.0, 0.0, -1.0),
		0.5,
		new lambertian(vec3(0.1, 0.2, 0.5))
	));

	// Ground
	obj_list.push_back(new sphere(
		vec3(0.0, -100.5, -1.0),
		100,
		new lambertian(vec3(0.8, 0.8, 0.0))
	));

	// Right metal
	obj_list.push_back(new sphere(
		vec3(1.0, 0.0, -1.0),
		0.5,
		new metal(vec3(0.8, 0.6, 0.2), 0.0)
	));

	// Left glass
	obj_list.push_back(new sphere(
		vec3(-1.0, 0.0, -1.0),
		0.5,
		new dielectric(1.5)
	));

	visible_list objects(obj_list);

	std::cout << "Progress: 0%";
	for(int y = 0; y < img->height; ++y) {
		for(int x = 0; x < img->width; ++x) {
			vec3 col;

			for(int i = 0; i < samples; ++i) {
				double u = double(x + drand48()) / double(img->width);
				double v = double(y + drand48()) / double(img->height);
				ray r = cam.get_ray(u, v);
				col += get_pixel(r, objects);
			}

			col /= double(samples);
			col = vec3(sqrt(col.x), sqrt(col.y), sqrt(col.z));

			img->set_pixel(x, img->height - y - 1, col);
		}

		float progress = (float(y) / float(img->height)) * 100.0;
		printf("\rProgress: %d%%", int(progress));
		std::cout.flush();
	}
	std::cout << std::endl;
}

int main() {
	const int width = 800;
	const int height = 400;
	const int samples = 256;

	image img(width, height);
	render(&img, samples);
	img.save("test.ppm");
}

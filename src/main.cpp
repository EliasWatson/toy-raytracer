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
#include <thread>

vec3 sky_color(const ray& r) {
	double t = 0.5 * (r.dir.y + 1.0);
	vec3 col = mix(vec3(1.0), vec3(0.5, 0.7, 1.0), t);

	double sun = dot(r.dir, normalize(vec3(0.0, 1.0, -1.0)));
	sun = step(0.95, sun);
	col = mix(col, vec3(4.0), sun);

	return col;
}

vec3 get_pixel(const ray& r, visible_list* world, int depth = 0) {
	if(depth > 64) return vec3(0.0);
	
	collision hit;
	if(world->intersects(r, 0.0, MAXFLOAT, hit)) {
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

vec3 sample_pixel(int x, int y, int width, int height, int samples, camera* cam, visible_list* objects) {
	vec3 col;

	for(int i = 0; i < samples; ++i) {
		double u = double(x + drand48()) / double(width);
		double v = double(y + drand48()) / double(height);
		ray r = cam->get_ray(u, v);
		col += get_pixel(r, objects);
	}

	col /= double(samples);
	col = vec3(sqrt(col.x), sqrt(col.y), sqrt(col.z));
	col.x = clamp(0.0, 1.0, col.x);
	col.y = clamp(0.0, 1.0, col.y);
	col.z = clamp(0.0, 1.0, col.z);

	return col;
}

void render_rows(image* img, camera* cam, visible_list* objects, int samples, int start_y, int end_y) {
	for(int y = start_y; y < end_y; ++y) {
		for(int x = 0; x < img->width; ++x) {
			vec3 col = sample_pixel(x, y, img->width, img->height, samples, cam, objects);
			img->set_pixel(x, img->height - y - 1, col);
		}
	}
}

void render(image* img, camera* cam, visible_list* objects, int samples, int threads) {
	std::thread thread_list[threads];

	double rows_per_thread = double(img->height) / double(threads);
	for(int i = 0; i < threads; ++i) {
		int start = rows_per_thread * i;
		int end = (start + rows_per_thread) + 1;
		if(i == (threads - 1)) end = img->height;

		thread_list[i] = std::thread(
			render_rows,
			img, cam, objects, samples, start, end
		);
	}

	for(int i = 0; i < threads; ++i) {
		thread_list[i].join();
	}
}

int main() {
	const int width = 800;
	const int height = 400;
	const int samples = 256;

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
		-0.45,
		new dielectric(1.5)
	));

	visible_list objects(obj_list);

	image img(width, height);
	render(&img, &cam, &objects, samples, 16);
	img.save("test.ppm");
}

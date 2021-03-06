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
#include <sstream>

vec3 sun_direction;

vec3 sky_color(const ray& r) {
	vec3 unit_dir = normalize(r.dir);

	double t = 0.5 * (unit_dir.y + 1.0);
	vec3 col = mix(vec3(1.0), vec3(0.5, 0.7, 1.0), t);

	//double sun = dot(unit_dir, sun_direction);
	//sun = step(0.95, sun);
	//col = mix(col, vec3(4.0), sun);

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

visible_list* random_scene() {
	std::vector<visible*> objects;
	int n = 500;

	objects.push_back(new sphere(vec3(0, -1000, 0), 1000, new lambertian(vec3(0.5))));

	int i = 1;
	for(int a = -11; a < 11; ++a) {
		for(int b = -11; b < 11; ++b) {
			double choose_mat = drand48();
			vec3 center(a+0.9*drand48(), 0.2, b+0.9*drand48());

			if(length(center - vec3(4, 0.2, 0)) > 0.9) {
				if(choose_mat < 0.8) {
					vec3 col(drand48()*drand48(), drand48()*drand48(), drand48()*drand48());
					objects.push_back(new sphere(center, 0.2, new lambertian(col)));
				} else if(choose_mat < 0.95) {
					vec3 col(0.5*(1+drand48()), 0.5*(1+drand48()), 0.5*(1+drand48()));
					objects.push_back(new sphere(center, 0.2, new metal(col, 0.5*drand48())));
				} else {
					objects.push_back(new sphere(center, 0.2, new dielectric(1.5)));
				}
			}
		}
	}

	objects.push_back(new sphere(vec3(0, 1, 0), 1.0, new dielectric(1.5)));
	objects.push_back(new sphere(vec3(-4, 1, 0), 1.0, new lambertian(vec3(0.4, 0.2, 0.1))));
	objects.push_back(new sphere(vec3(4, 1, 0), 1.0, new metal(vec3(0.7, 0.6, 0.5), 0.0)));

	return new visible_list(objects);
}

int main() {
	const int width = 640;
	const int height = 480;
	const int samples = 16;

	vec3 cam_pos(13.0, 2.0, 3.0);
	vec3 look_at(0.0, 0.0, 0.0);
	double dist_to_focus = length(cam_pos - look_at);
	double aperture = 0.1;

	camera cam(
		cam_pos,
		look_at,
		vec3(0.0, 1.0, 0.0),
		20,
		double(width) / double(height),
		aperture,
		dist_to_focus
	);

	visible_list* world = random_scene();

	sun_direction = normalize(vec3(0.0, 1.0, -1.0));

	image img(width, height);
	render(&img, &cam, world, samples, 16);
	img.save("test.ppm");
}

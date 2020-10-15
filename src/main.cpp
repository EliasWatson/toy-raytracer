#include "image.h"
#include "vec3.h"
#include "ray.h"
#include "util.h"

vec3 color(const ray& r) {
	float t = 0.5 * (r.dir.y + 1.0);
	return mix(vec3(1.0), vec3(0.5, 0.7, 1.0), t);
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
			vec3 col = color(r);

			img->set_pixel(x, img->height - y - 1, col);
		}
	}
}

int main() {
	const int width = 640;
	const int height = 480;

	image img(width, height);
	render(&img);
	img.save("test.ppm");
}

#include "image.h"

#include <cassert>
#include <fstream>

image::image(int width, int height) {
	assert(width > 0 && height > 0);
	this->width = width;
	this->height = height;
	this->data = std::vector<std::vector<vec3>>(height, std::vector<vec3>(width));
}

void image::set_pixel(int x, int y, vec3 p) {
	assert(x >= 0 && x < this->width && y >= 0 && y < this->height);
	this->data[y][x] = p;
}

vec3 image::get_pixel(int x, int y) {
	assert(x >= 0 && x < this->width && y >= 0 && y < this->height);
	return this->data[y][x];
}

void image::save(std::string path) {
	std::ofstream file;
	file.open(path.c_str());

	file << "P3\n" << this->width << " " << this->height << "\n255\n";

	for(int y = 0; y < this->height; ++y) {
		for(int x = 0; x < this->width; ++x) {
			vec3 p = this->get_pixel(x, y);

			int ir = int(255.99 * p.x);
			int ig = int(255.99 * p.y);
			int ib = int(255.99 * p.z);

			file << ir << " " << ig << " " << ib << "\n";
		}
	}

	file.close();
}

#ifndef H_IMAGE
#define H_IMAGE

#include <vector>
#include <string>

#include "vec3.h"

struct image {
	int width, height;
	std::vector<std::vector<vec3>> data;

	image(int width, int height);

	void set_pixel(int x, int y, vec3 p);

	vec3 get_pixel(int x, int y);

	void save(std::string path);
};

#endif

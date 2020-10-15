#include "image.h"
#include "vec3.h"

int main() {
	image img(640, 480);

	for(int y = 0; y < 480; ++y) {
		for(int x = 0; x < 640; ++x) {
			vec3 col(
				float(x) / float(640),
				float(y) / float(480),
				0.2
			);
			img.set_pixel(x, y, col);
		}
	}

	img.save("test.ppm");
}

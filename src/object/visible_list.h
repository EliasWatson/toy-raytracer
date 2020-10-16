#ifndef H_VISIBLE_LIST
#define H_VISIBLE_LIST

#include "visible.h"
#include <vector>

class visible_list: public visible {
public:
	std::vector<visible*> objects;

	visible_list() { }
	visible_list(std::vector<visible*> objects) : objects(objects) { }

	virtual bool intersects(const ray& r, double dist_min, double dist_max, collision& data) const {
		collision temp_collision;
		bool collision_occured = false;
		double closest_dist = dist_max;

		for(const auto& obj : objects) {
			if(obj->intersects(r, dist_min, closest_dist, temp_collision)) {
				collision_occured = true;
				closest_dist = temp_collision.dist;
				data = temp_collision;
			}
		}

		return collision_occured;
	}
};

#endif

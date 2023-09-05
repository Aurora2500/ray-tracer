#ifndef BVH_HPP_
#define BVH_HPP_

#include "hittable.hpp"

#include <memory>
#include <vector>

class bvh_node : public hittable {
private:
	aabb m_bbox;
	std::shared_ptr<hittable> m_left, m_right;

public:
	bvh_node(const std::vector<std::shared_ptr<hittable>> &objects, int start, int end, int axis = 0);

	bool hit(const ray &r, interval t_lim, hit_record &rec) const override;

	aabb bounding_box() const override;
};

#endif
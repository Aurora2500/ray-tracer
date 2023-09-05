#include "bvh.hpp"
#include <algorithm>

auto comparator_x = [](const std::shared_ptr<hittable> &a, const std::shared_ptr<hittable> &b) {
	return a->bounding_box().axis(0).min < b->bounding_box().axis(0).min;
};
auto comparator_y = [](const std::shared_ptr<hittable> &a, const std::shared_ptr<hittable> &b) {
	return a->bounding_box().axis(1).min < b->bounding_box().axis(1).min;
};
auto comparator_z = [](const std::shared_ptr<hittable> &a, const std::shared_ptr<hittable> &b) {
	return a->bounding_box().axis(2).min < b->bounding_box().axis(2).min;
};

bvh_node::bvh_node(const std::vector<std::shared_ptr<hittable>> &src_objects, int start, int end, int axis)
{
	auto objects = src_objects;
	size_t span = end - start;

	auto comparator =
		axis == 0 ? comparator_x
		: axis == 1 ? comparator_y
		: comparator_z;

	if(span == 1) {
		m_left = m_right = objects[start];
	} else if(span == 2) {
		if(comparator(objects[start], objects[start + 1])) {
			m_left = objects[start];
			m_right = objects[start + 1];
		} else {
			m_left = objects[start + 1];
			m_right = objects[start];
		}
	} else {
		std::sort(objects.begin() + start, objects.begin() + end, comparator);

		int mid = start + span / 2;
		m_left = std::make_shared<bvh_node>(objects, start, mid, (axis + 1) % 3);
		m_right = std::make_shared<bvh_node>(objects, mid, end, (axis + 1) % 3);
	}

	m_bbox = aabb(m_left->bounding_box(), m_right->bounding_box());
}

bool bvh_node::hit(const ray &r, interval t_lim, hit_record &rec) const
{
	if (!m_bbox.hit(r, t_lim))
		return false;
	
	bool hit_left = m_left->hit(r, t_lim, rec);
	bool hit_right = m_right->hit(r, interval(t_lim.min, hit_left? rec.t : t_lim.max), rec);

	return hit_left || hit_right;
}

aabb bvh_node::bounding_box() const
{
	return m_bbox;
}

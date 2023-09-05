#ifndef HIT_LIST_HPP_
#define HIT_LIST_HPP_

#include "hittable.hpp"
#include "sphere.hpp"
#include "aabb.hpp"

#include <vector>
#include <memory>

class hittable_list : public hittable {
private:
	std::vector<std::shared_ptr<hittable>> m_objects;
	aabb m_bbox;
public:
	void add(std::shared_ptr<hittable> s);
	size_t size() const { return m_objects.size(); }
	bool hit(const ray &r, interval t_lim, hit_record &rec) const override;
	aabb bounding_box() const override;
	void bake();
};

#endif
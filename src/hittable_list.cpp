#include "hittable_list.hpp"
#include "bvh.hpp"

void hittable_list::add(std::shared_ptr<hittable> obj)
{
	m_bbox = aabb(m_bbox, obj->bounding_box());
	m_objects.push_back(obj);
}

bool hittable_list::hit(const ray &r, interval t_lim, hit_record &rec) const
{
	hit_record temp_rec;
	bool hit_anything = false;
	double closest_so_far = t_lim.max;

	for (const auto &s : m_objects) {
		if (s->hit(r, interval(t_lim.min, closest_so_far), temp_rec)) {
			hit_anything = true;
			closest_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}

	return hit_anything;
}

aabb hittable_list::bounding_box() const
{
	return m_bbox;
}

void hittable_list::bake()
{
	std::cout << "baking world of " << m_objects.size() << " elements" << std::endl;
	auto bvh_root = std::make_shared<bvh_node>(m_objects, 0, m_objects.size());
	m_objects.clear();
	m_objects.push_back(bvh_root);
	m_bbox = bvh_root->bounding_box();
}

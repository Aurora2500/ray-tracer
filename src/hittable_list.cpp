#include "hittable_list.hpp"

void hittable_list::add(sphere s)
{
	m_spheres.push_back(s);
}

bool hittable_list::hit(const ray &r, interval t_lim, hit_record &rec) const
{
	hit_record temp_rec;
	bool hit_anything = false;
	double closest_so_far = t_lim.max;

	for (const sphere &s : m_spheres) {
		if (s.hit(r, interval(t_lim.min, closest_so_far), temp_rec)) {
			hit_anything = true;
			closest_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}

	return hit_anything;
}
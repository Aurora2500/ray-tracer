#ifndef HIT_LIST_HPP_
#define HIT_LIST_HPP_

#include "hittable.hpp"
#include "sphere.hpp"

#include <vector>

class hittable_list : public hittable {
private:
	std::vector<sphere> m_spheres;
public:
	void add(sphere s);
	bool hit(const ray &r, interval t_lim, hit_record &rec) const override;
};

#endif
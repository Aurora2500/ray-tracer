#include "interval.hpp"
#include <cmath>
#include <algorithm>

interval::interval()
	: min(+INFINITY), max(-INFINITY)
{
}

interval::interval(double min, double max)
	: min(min), max(max)
{
}

interval::interval(const interval &a, const interval &b)
	: min(std::min(a.min, b.min)), max(std::max(a.max, b.max))
{
}

bool interval::containsOpen(double x) const
{
	return min < x && x < max;
}

bool interval::containsClosed(double x) const
{
	return min <= x && x <= max;
}

double interval::clamp(double x) const
{
	if (x < min) return min;
	if (x > max) return max;
	return x;
}

interval interval::expand(double delta) const
{
	double padding = delta / 2.0;
	return interval(min - padding, max + padding);
}

double interval::size() const
{
	if (max <= min) return 0.0;
	return max - min;
}

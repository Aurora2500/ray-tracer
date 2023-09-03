#include "interval.hpp"

interval::interval(double min, double max)
	: min(min), max(max)
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
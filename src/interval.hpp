#ifndef INTERVAL_HPP_
#define INTERVAL_HPP_

struct interval {
	double min, max;

	interval(double min, double max);
	bool containsOpen(double x) const;
	bool containsClosed(double x) const;
	double clamp(double x) const;
};

#endif
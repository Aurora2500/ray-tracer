#ifndef INTERVAL_HPP_
#define INTERVAL_HPP_

struct interval {
	double min, max;

	interval();
	interval(double min, double max);
	interval(const interval &a, const interval &b);
	bool containsOpen(double x) const;
	bool containsClosed(double x) const;
	double clamp(double x) const;
	interval expand(double delta) const;
	double size() const;
};

#endif
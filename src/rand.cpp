#include <cmath>
#include <cstdlib>
#include "rand.hpp"

const double PI = 3.1415926535897932385;

double random_double()
{
	return rand() / (RAND_MAX + 1.0);
}

double random_double(double max)
{
	return random_double() * max;
}
double random_double(double min, double max)
{
	return min + (max - min) * random_double();
}

double norm(double mean, double std)
{
	double u1 = 1.0 - random_double();
	double u2 = random_double();
	double z0 = std::sqrt(-2.0 * std::log(u1)) * std::cos(2.0 * PI * u2);
	return mean + std * z0;
}

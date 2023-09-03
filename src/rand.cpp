#include <cmath>
#include <cstdlib>

double random_double()
{
	return rand() / (RAND_MAX + 1.0);
}

double random_double(double min, double max)
{
	return min + (max - min) * random_double();
}

double norm(double mean, double std)
{
	double u1 = 1.0 - random_double();
	double u2 = random_double();
	double z0 = std::sqrt(-2.0 * std::log(u1)) * std::cos(2.0 * M_PI * u2);
	return mean + std * z0;
}
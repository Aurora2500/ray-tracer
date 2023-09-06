#include "mutation.hpp"
#include <cstdlib>

void ga::mutateBitFlip(std::vector<bool> &chromosome, float mutationRate)
{
	for(int i = 0; i < chromosome.size(); ++i)
	{
		if((rand() / (float)RAND_MAX) < mutationRate)
		{
			chromosome[i] = !chromosome[i];
		}
	}
}
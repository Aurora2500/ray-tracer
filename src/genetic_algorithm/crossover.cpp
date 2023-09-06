#include "crossover.hpp"
#include <cstdlib>

void ga::crossoverOnePoint(const std::vector<bool> &parent1, const std::vector<bool> &parent2, std::vector<bool> &child1, std::vector<bool> &child2)
{
	auto crossoverPoint = rand() % parent1.size();
	for (int i = 0; i < crossoverPoint; ++i)
	{
		child1[i] = parent1[i];
		child2[i] = parent2[i];
	}
	for (int i = crossoverPoint; i < parent1.size(); ++i)
	{
		child1[i] = parent2[i];
		child2[i] = parent1[i];
	}
}

void ga::crossoverUniform(const std::vector<bool> &parent1, const std::vector<bool> &parent2, std::vector<bool> &child1, std::vector<bool> &child2, float crossoverRate)
{
	for (int i = 0; i < parent1.size(); ++i)
	{
		if ((rand() / (float)RAND_MAX) < crossoverRate)
		{
			child1[i] = parent1[i];
			child2[i] = parent2[i];
		}
		else
		{
			child1[i] = parent2[i];
			child2[i] = parent1[i];
		}
	}
}
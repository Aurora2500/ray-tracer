#include "selection.hpp"
#include <cstdlib>

void ga::selectTournament(const std::vector<std::vector<bool>> &population, const std::vector<float> &fitness, std::vector<std::vector<bool>> &newPopulation, std::vector<float> &newFitness, size_t newSize)
{
	newPopulation.reserve(newSize);
	newFitness.reserve(newSize);

	for(int k = 0; k < newSize; k++) {
		size_t index1 = rand() % population.size();
		size_t index2 = rand() % population.size();
		size_t winner = fitness[index1] < fitness[index2] ? index1 : index2;
		newPopulation.push_back(population[winner]);
		newFitness.push_back(fitness[winner]);
	}
}
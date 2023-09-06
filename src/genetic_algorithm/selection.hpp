#ifndef GA_SELECTION_HPP_
#define GA_SELECTION_HPP_

#include <vector>

namespace ga {

void 
selectTournament(
	const std::vector<std::vector<bool>>& population,
	const std::vector<float>& fitness,
	std::vector<std::vector<bool>> &newPopulation,
	std::vector<float>& newFitness,
	size_t newSize
);

}

#endif
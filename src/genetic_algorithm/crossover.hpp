#ifndef GA_CROSSOVER_HPP_
#define GA_CROSSOVER_HPP_

#include <vector>

namespace ga {

void crossoverOnePoint(const std::vector<bool> &parent1, const std::vector<bool> &parent2, std::vector<bool> &child1, std::vector<bool> &child2);

void crossoverUniform(const std::vector<bool> &parent1, const std::vector<bool> &parent2, std::vector<bool> &child1, std::vector<bool> &child2, float crossoverRate);

}

#endif
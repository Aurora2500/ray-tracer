#ifndef GA_ALGORITHM_HPP_
#define GA_ALGORITHM_HPP_

#include <vector>
#include <functional>

namespace ga {


class BinaryAlgorithm {
private:
	std::vector<std::vector<bool>> m_population;
	std::vector<float> m_fitness;
	std::vector<bool> m_hof;
	float m_hofFitness;
	int m_generation;
	int m_popSize, m_chromosomeSize;
	float m_mutationProb, m_crossoverProb;
	std::function<float(const std::vector<bool>&)> m_fitnessFunction;

public:
	BinaryAlgorithm(int popSize, int chromosomeSize, std::function<float(const std::vector<bool>&)> fitnessFunction, float mutProb, float crossProb);

	void init();
	void step();
	void run(int generations);

	int generation() const;
	const std::vector<bool>& hof() const;
	const std::vector<bool>& population(int i) const;
	float fitness(int i) const;
};

};

#endif
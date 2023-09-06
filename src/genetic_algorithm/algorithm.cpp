#include "algorithm.hpp"
#include <cstdlib>
#include <cmath>

#include "selection.hpp"
#include "mutation.hpp"
#include "crossover.hpp"

ga::BinaryAlgorithm::BinaryAlgorithm(int popSize, int chromosomeSize, std::function<float(const std::vector<bool> &)> fitnessFunction, float mutProb, float crossProb)
	: m_popSize(popSize)
	, m_chromosomeSize(chromosomeSize)
	, m_fitnessFunction(fitnessFunction)
	, m_generation(0)
	, m_mutationProb(mutProb)
	, m_crossoverProb(crossProb)
{
	m_population.resize(m_popSize);
	m_fitness.resize(m_popSize);
	m_hofFitness = - INFINITY;
}

void ga::BinaryAlgorithm::init()
{
	for(int i = 0; i < m_popSize; ++i)
	{
		m_population[i].resize(m_chromosomeSize);
		for(int j = 0; j < m_chromosomeSize; ++j)
		{
			m_population[i][j] = static_cast<bool>(rand() % 2);
		}
		m_fitness[i] = m_fitnessFunction(m_population[i]);
	}
}

void ga::BinaryAlgorithm::step()
{
	std::vector<std::vector<bool>> newPopulation;
	std::vector<float> newFitness; 
	selectTournament(m_population, m_fitness, newPopulation, newFitness, m_popSize);
	
	for(int i = 0; i < m_popSize; i += 2)
	{
		if((rand() / (float)RAND_MAX) < m_crossoverProb)
		{
			crossoverUniform(newPopulation[i], newPopulation[i + 1], newPopulation[i], newPopulation[i + 1], 0.3f);
			newFitness[i] = std::numeric_limits<double>::quiet_NaN();
			newFitness[i + 1] = std::numeric_limits<double>::quiet_NaN();
		}
	}

	for(int i = 0; i < m_popSize; i++)
	{
		if ((rand() / (float)RAND_MAX) < m_mutationProb)
		{
			mutateBitFlip(newPopulation[i], 0.05f);
			newFitness[i] = std::numeric_limits<double>::quiet_NaN();
		}
	}

	for(int i = 0; i < m_popSize; i++)
	{
		if (std::isnan(newFitness[i]))
		{
			newFitness[i] = m_fitnessFunction(newPopulation[i]);
		}

		if (newFitness[i] > m_hofFitness)
		{
			m_hof = newPopulation[i];
			m_hofFitness = newFitness[i];
		}
	}

	m_population = newPopulation;
	m_fitness = newFitness;
}

void ga::BinaryAlgorithm::run(int generation)
{
	for(int i = 0; i < generation; i++)
	{
		step();
	}
}

const std::vector<bool> &ga::BinaryAlgorithm::hof() const
{
	return m_hof;
}

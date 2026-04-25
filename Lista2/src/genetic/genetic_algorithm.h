//
// Created by mikol on 23.04.2026.
//

#ifndef GENETIC_H
#define GENETIC_H

#include <vector>
#include <random>

struct Individual {
    std::vector<int> weights;
    bool preferCenter;
    int wins = 0;
    int games = 0;

    double winRate() const { return games == 0 ? 0 : static_cast<double>(wins) / games; }
};

class GeneticAlgorithm {
    int populationSize;
    int generations;
    int searchDepth;
    int matchesPerIndividual = 5;
    int eliteFraction = 4;
    std::mt19937 rng{std::random_device{}()};

public:
    GeneticAlgorithm(int populationSize, int generations, int searchDepth);

    std::vector<Individual> run();

private:
    std::vector<Individual> initPopulation();
    void playMatch(Individual& a, Individual& b);
    Individual crossover(const Individual& a, const Individual& b);
    void mutate(Individual& a);
};



#endif //GENETIC_H

//
// Created by mikol on 23.04.2026.
//

#include "genetic_algorithm.h"

#include <algorithm>
#include <iostream>
#include "agent.h"

std::vector<Individual> GeneticAlgorithm::initPopulation() {
    std::vector<Individual> population;
    std::uniform_int_distribution<> weightDist(1, 20);
    std::uniform_int_distribution<> boolDist(0, 1);

    for (int i = 0; i < populationSize; i++) {
        Individual ind;
        for (int j = 0; j < 5; j++) {
            ind.weights.push_back(weightDist(rng));
        }
        ind.preferCenter = boolDist(rng);
        population.push_back(ind);
    }

    return population;
}


GeneticAlgorithm::GeneticAlgorithm(int populationSize, int generations, int searchDepth)
    : populationSize(populationSize), generations(generations), searchDepth(searchDepth) {
}


void GeneticAlgorithm::mutate(Individual &a) {
    std::uniform_int_distribution<> indexDist(0, static_cast<int>(a.weights.size()) - 1);
    std::uniform_int_distribution<> deltaDist(-2, 2);
    std::uniform_int_distribution<> chanceDist(0, 9);

    int i = indexDist(rng);
    a.weights[i] += deltaDist(rng);
    if (a.weights[i] < 1) a.weights[i] = 1;
    if (a.weights[i] > 20) a.weights[i] = 20;

    if (chanceDist(rng) == 0) a.preferCenter = !a.preferCenter;
}

void GeneticAlgorithm::playMatch(Individual &a, Individual &b) {
    Board board;
    Evaluator evalA(a.weights, a.preferCenter);
    Evaluator evalB(b.weights, b.preferCenter);
    Agent agent;

    int rounds = 0;
    while (board.getGameState() == ongoing && rounds < 200) {
        board.makeMove(agent.getBestMove(board, white_player, evalA, searchDepth));
        if (board.getGameState() != ongoing) break;
        board.makeMove(agent.getBestMove(board, black_player, evalB, searchDepth));
        rounds++;
    }

    game_state result = board.getGameState();
    if (result == white_won) { a.wins++; }
    else if (result == black_won) { b.wins++; }
    a.games++;
    b.games++;
}

Individual GeneticAlgorithm::crossover(const Individual &a, const Individual &b) {
    std::uniform_int_distribution<> boolDist(0, 1);

    Individual child;
    for (int i = 0; i < static_cast<int>(a.weights.size()); i++) {
        child.weights.push_back(boolDist(rng) ? a.weights[i] : b.weights[i]);
    }
    child.preferCenter = boolDist(rng) ? a.preferCenter : b.preferCenter;
    return child;
}

std::vector<Individual> GeneticAlgorithm::run() {
    auto population = initPopulation();

    for (int gen = 0; gen < generations; gen++) {
        for (auto& ind : population) {
            ind.wins = 0;
            ind.games = 0;
        }

        for (int i = 0; i < populationSize; i++) {
            std::vector<int> opponents;
            for (int j = 0; j < populationSize; j++) {
                if (i != j) opponents.push_back(j);
            }

            std::ranges::shuffle(opponents, rng);
            int matchCount = std::min(matchesPerIndividual, static_cast<int>(opponents.size()));

            for (int k = 0; k < matchCount; k++) {
                playMatch(population[i], population[opponents[k]]);
                playMatch(population[opponents[k]], population[i]);
            }
        }

        std::sort(population.begin(), population.end(),
                [](const Individual& a, const Individual& b) {
                    return a.winRate() > b.winRate();
                });

        int eliteSize = populationSize / eliteFraction;
        for (int i = eliteSize; i < populationSize; i++) {
            std::uniform_int_distribution<> eliteDist(0, eliteSize - 1);
            int a = eliteDist(rng);
            int b = eliteDist(rng);
            population[i] = crossover(population[a], population[b]);
            mutate(population[i]);
        }

        std::cout << "Gen " << gen << " best winrate: " << population[0].winRate() << std::endl;
        std::cout << "Weights: ";
        for (int weight: population[0].weights) std::cout << weight << " ";
        std::cout << "Prefer: " << (population[0].preferCenter ? "Prefers center" : "Prefers sides") << std::endl;
        std::cout << "Played games: " << population[0].games << std::endl;
    }
    return population;
}
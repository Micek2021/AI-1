//
// Created by mikol on 25.04.2026.
//

#include "test_genetic.h"
#include "genetic_algorithm.h"
#include <iostream>
#include <chrono>


void runGenetic(int populationSize, int generations, int depth) {
    /* GENETIC ALGORITHM  */

    auto start = std::chrono::high_resolution_clock::now();
    GeneticAlgorithm genetic(populationSize, generations, depth);
    auto population = genetic.run();
    Individual best = population[0];

    std::cout << "Best strategie : ";
    for (int w : best.weights) std::cout << w << " ";
    std::cout << "\npreferCenter: " << (population[0].preferCenter ? "Prefers center" : "Prefers sides") << "\n";
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);

    std::cerr << "Time: " << duration.count() << " seconds" << std::endl;
}
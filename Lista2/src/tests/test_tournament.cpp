//
// Created by mikol on 25.04.2026.
//

#include "test_tournament.h"
#include "agent.h"
#include <iostream>
#include <map>

#include "test_game.h"


void runTournament(std::vector<NamedEvaluator>& competitors, int depth) {
   /*TOURNAMENT*/

    std::map<std::string, int> scoreboard;
    for (const auto& comp : competitors) scoreboard[comp.name] = 0;

    std::cout << "Starting tournament 1v1...\n";
    std::cout << "------------------------------------------\n";

    for (size_t i = 0; i < competitors.size(); ++i) {
        for (size_t j = 0; j < competitors.size(); ++j) {
            if (i == j) continue;


            game_state result = runGame(competitors[i].eval, competitors[j].eval, depth, false);
            std::cout << competitors[i].name << " vs " << competitors[j].name << ": ";

            if (result == white_won) {
                std::cout << "Won " << competitors[i].name << " (White)\n";
                scoreboard[competitors[i].name]++;
            } else if (result == black_won) {
                std::cout << "Won " << competitors[j].name << " (Black)\n";
                scoreboard[competitors[j].name]++;
            } else {
                std::cout << "Tie/Hit round limit\n";
            }
        }
    }


    std::cout << "\n--- Scoreboard ---\n";
    for (const auto& entry : scoreboard) {
        std::cout << entry.first << ": " << entry.second << " wins\n";
    }
}

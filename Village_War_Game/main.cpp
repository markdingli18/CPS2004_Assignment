#include <iostream>
#include <vector>
#include "header.h"

int main() {

    // Call the Game_Setup function to initialize the game
    Game_Setup(num_players, num_AIs, villages);

    // Generate the player and AI villages and place them on the map
    for (int i = 0; i < num_players; i++) {
        CreateVillage(0, 0, false, villages);
    }
    for (int i = 0; i < num_AIs; i++) {
        CreateVillage(0, 0, true, villages);
    }

    //// Checking
    // Check that one village is generated for each player and AI
    if (villages.size() != num_players + num_AIs) {
        std::cout << "----------------------------------------------------------------------\n" << std::endl;
        std::cout << "Error: The number of generated villages does not match the number of players and AIs." << std::endl;
        std::cout << "\t\tPLEASE RESTART THE GAME!!\n" << std::endl;
        std::cout << "----------------------------------------------------------------------\n" << std::endl;
    }

    // Check that the villages are placed on the map
    for (const Village& village : villages) {
        if (map[village.x][village.y] != 1) {
            std::cout << "----------------------------------------------------------------------\n" << std::endl;
            std::cout << "Error: Village not found at expected coordinates on the map." << std::endl;
            std::cout << "\t\tPLEASE RESTART THE GAME!!\n" << std::endl;
            std::cout << "----------------------------------------------------------------------\n" << std::endl;
        }
    }

    // Print the map to the console
    // PrintMap(map);

    return 0;
}

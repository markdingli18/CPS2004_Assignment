#include <iostream>
#include <vector>

// Declare the constants for the map dimensions
const int MAP_WIDTH = 100;
const int MAP_HEIGHT = 100;

struct Village {
    int x;
    int y;
    bool isAI;
};

// Declare the map array at the global scope
int map[MAP_WIDTH][MAP_HEIGHT];

// Generate a village and place it on the map
void CreateVillage(int x, int y, bool isAI, std::vector<Village>& villages) {
    // Check if the x and y coordinates are within the boundaries of the map
    if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT) {
        std::cout << "Error: The village coordinates are out of bounds." << std::endl;
        return;
    }

    Village village;
    village.x = x;
    village.y = y;
    village.isAI = isAI;

    // Update the map cell at the village coordinates to 1
    map[x][y] = 1;

    villages.push_back(village);
}

// Function to print Map
//void PrintMap(int map[MAP_WIDTH][MAP_HEIGHT]) {
//    for (int i = 0; i < MAP_WIDTH; i++) {
//        for (int j = 0; j < MAP_HEIGHT; j++) {
//            if (map[i][j] == 1) {
//                std::cout << 'V' << " ";
//            } else {
//                std::cout << map[i][j] << " ";
//            }
//        }
//        std::cout << std::endl;
//    }
//}

// Initialize the game
void Game_Setup(int& num_players, int& num_AIs, std::vector<Village>& villages) {
    // Display the top border
    std::cout << "----------------------------------------------------------------------\n" << std::endl;

    // Display the welcome message
    std::cout << "\t\tWELCOME TO VILLAGE WAR!" << std::endl;
    std::cout << "ASSEMBLE YOUR TROOPS AND DEFEND YOUR VILLAGE FROM INVADING FORCES!" << std::endl;
    std::cout << "\t   MAY THE GODS BE WITH YOU IN BATTLE.\n" << std::endl;

    // Display the bottom border
    std::cout << "----------------------------------------------------------------------\n" << std::endl;

    // Prompt the user for the number of players until a valid number is entered
    while (true) {
        std::cout << "Enter the number of players (at least one): ";
        std::cin >> num_players;
        std::cout << "\n----------------------------------------------------------------------" << std::endl;

        // Check if the number of players is valid (at least one player)
        if (num_players > 0) {
            break;  // Valid input, exit the loop
        }

        // Invalid input, display an error message and continue the loop
        std::cout << "\n Error: The number of players must be at least one." << std::endl;
        std::cout << "\n----------------------------------------------------------------------\n" << std::endl;
    }

    // Prompt the user for the number of AIs until a valid number is entered
    while (true) {
        std::cout << "\nEnter the number of AIs (zero or more): ";
        std::cin >> num_AIs;
        std::cout << "\n----------------------------------------------------------------------" << std::endl;

        // Check if the number of AIs is valid (zero or more)
        if (num_AIs >= 0) {
            break;  // Valid input, exit the loop
        }

        // Invalid input, display an error message and continue the loop
        std::cout << "\nError: The number of AIs must be zero or more." << std::endl;
        std::cout << "\n----------------------------------------------------------------------" << std::endl;

    }
}
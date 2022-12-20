#ifndef VILLAGE_WAR_GAME_HEADER_H
#define VILLAGE_WAR_GAME_HEADER_H

#include <iostream>
#include <vector>

const int MAP_WIDTH = 100;  // Width of the map
const int MAP_HEIGHT = 100;  // Height of the map

//// Structs
// Define the Building struct
struct Building {
    std::string name;  // Name of the building
    int level;  // Level of the building
    int health;  // Health of the building
};

// Define the Troop struct
struct Troop {
    std::string name;  // Name of the troop
    int level;  // Level of the troop
    int attack;  // Attack power of the troop
    int defense;  // Defense power of the troop
    int health;  // Health of the troop
};

// Define the Village struct
struct Village {
    int x;  // x-coordinate of the village on the map
    int y;  // y-coordinate of the village on the map
    bool isAI;  // Indicates whether the village is controlled by an AI
    int health;  // Health of the village
    std::vector<Building> buildings;  // Vector to store the buildings in the village
    std::vector<Troop> troops;  // Vector to store the troops in the village
};

//// Variables
extern int map[MAP_WIDTH][MAP_HEIGHT];
int num_players, num_AIs;               // Declare variables to store the number of players and AIs
std::vector<Village> villages;          // Declare a vector to store the villages
int resource1, resource2, resource3;    // Declare resource variables
int turn;                               // Declare turn variable

//// Functions
// Initialize the game
void Game_Setup(int& num_players, int& num_AIs, std::vector<Village>& villages);

// Generate a village and place it on the map
void CreateVillage(int x, int y, bool isAI, std::vector<Village>& villages);

// Print the map to the console
// void PrintMap(int map[MAP_WIDTH][MAP_HEIGHT]);

#endif //VILLAGE_WAR_GAME_HEADER_H
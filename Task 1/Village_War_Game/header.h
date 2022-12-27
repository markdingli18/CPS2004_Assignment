#ifndef MAIN_CPP_HEADER_H // include guard to prevent multiple inclusions of the header file
#define MAIN_CPP_HEADER_H

#include <iostream> // for input/output streams
#include <vector> // for std::vector
#include <cstdlib> // for various general purpose functions
#include <ctime> // for time functions
#include <random> // for random number generation
#include <cstdlib>

#define MAP_HEIGHT 20 // define the height of the map to be 20 cells
#define MAP_WIDTH 20 // define the width of the map to be 20 cells

////--------------------------------------------------------------------------------------------------------------------

//// Structs

// Struct to represent a map in the game
struct Map {
    int width; // width of the map in cells
    int height; // height of the map in cells
    std::vector<std::vector<int>> cells; // 2D vector representing the cells of the map
};

// Struct to represent resources in the game
struct Resources {
    int wood; // amount of wood
    int gold; // amount of gold
    int food; // amount of food
};

// Struct to represent a building in the game
struct Building {
    std::string type; // Type of building (e.g. "ResourceGenerator", "TroopGenerator")
    std::string name; // Name of the building (e.g. "Gold Mine", "Archery Range")
    int level; // Current level of the building
    int resourceGenerationRate; // Rate at which the building generates resources (if applicable)
    int troopGenerationCost; // Cost to generate a troop (if applicable)
    Resources costToUpgrade; // Cost to upgrade the building
};

// Struct to represent a troop in the game
struct Troop {
    std::string type; // Type of troop (e.g. "Sword", "Archer", "Cavalry")
    int attack; // attack strength of the troop
    int defense; // defense strength of the troop
    int health; // health of the troop
    int trainingCost; // cost to train the troop
    int carryingCapacity; // carrying capacity of the troop
};

// Struct to represent a village in the game
struct Village {
//std::string name; // name of the village
    int x; // x coordinate of the village
    int y; // y coordinate of the village
    int health; // health of the village
    bool isPlayer; // flag to indicate whether the village belongs to the player or an AI
    std::vector<Building> buildings; // vector of buildings in the village
    std::vector<Troop> troops; // vector of troops in the village
    Resources resources; // resources owned by the village
};

////--------------------------------------------------------------------------------------------------------------------

//// Functions

// Function to generate a map with the given width and height
Map generateMap(int width, int height);

// Function to print the given map and villages to the console
void printMap(const Map& map, const std::vector<Village>& villages);

// Function to generate a vector of troops for the given village
std::vector<Troop> generateTroops(Village &village);

// Function to generate a vector of buildings for the given village
std::vector<Building> generateBuildings(Village &village);

// Function to upgrade the given building in the given village
// Returns true if the upgrade was successful, false otherwise
bool upgradeBuilding(Village &village, Building &building);

// Function to generate a vector of villages for the given number of players and AIs
std::vector<Village> generateVillages(int numPlayers, int numAIs);

// Function to generate resources for the given village
void generateResources(Village &village);

// Function to print a welcome message to the console
void welcome_message();

// Function to print information about the given villages to the console
void villages_info(const std::vector<Village> &newVillages);

// Function to check if the game is still running
// Returns true if the game is running, false otherwise
bool gameIsRunning();

// Function to check if the player has won the game
// Returns true if the player has won, false otherwise
bool winGame(std::vector<Village> &villages);

// Function to allow the player to attack another village
void attackVillage(Village &attackingVillage, Village &defendingVillage);

// Function to allow an AI to attack another village
void aiAttackVillage(Village &attacker, Village &defender);

// Function to allow the player to take their turn
void takePlayerTurn(Village &village, std::vector<Village> &villages);

// Function to allow an AI to take their turn
void takeAITurn(Village &village);

////--------------------------------------------------------------------------------------------------------------------

#endif //MAIN_CPP_HEADER_H
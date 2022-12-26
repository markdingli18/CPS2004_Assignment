#ifndef MAIN_CPP_HEADER_H
#define MAIN_CPP_HEADER_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <random>

#define MAP_HEIGHT 20
#define MAP_WIDTH 20

////--------------------------------------------------------------------------------------------------------------------

//// Structs
struct Map {
    int width;
    int height;
    std::vector<std::vector<int>> cells;
};

struct Resources {
    int wood;
    int gold;
    int food;
};

struct Building {
    std::string type; // Type of building (e.g. "ResourceGenerator", "TroopGenerator")
    std::string name; // Name of the building (e.g. "Gold Mine", "Archery Range")
    int level; // Current level of the building
    int resourceGenerationRate; // Rate at which the building generates resources (if applicable)
    int troopGenerationCost; // Cost to generate a troop (if applicable)
    Resources costToUpgrade;
};

struct Troop {
    std::string type; // Type of troop (e.g. "Sword", "Archer", "Cavalry")
    int attack;
    int defense;
    int health;
    int trainingCost;
    int carryingCapacity;
};

struct Village {
    //std::string name;
    int x; // x coordinate of the village
    int y; // y coordinate of the village
    int health; // health of the village
    bool isPlayer; // flag to indicate whether the village belongs to the player or an AI
    std::vector<Building> buildings; // vector of buildings in the village
    std::vector<Troop> troops; // vector of troops in the village
    Resources resources;
};

////--------------------------------------------------------------------------------------------------------------------
//// Functions
Map generateMap(int width, int height);
void printMap(const Map& map, const std::vector<Village>& villages);
std::vector<Troop> generateTroops(Village &village);
std::vector<Building> generateBuildings(Village &village);
bool upgradeBuilding(Village &village, Building &building);
std::vector<Village> generateVillages(int numPlayers, int numAIs);
void generateResources(Village &village);
void welcome_message();
void villages_info(const std::vector<Village> &newVillages);
bool gameIsRunning();
bool winGame(std::vector<Village> &villages);
void attackVillage(Village &attackingVillage, Village &defendingVillage);
void aiAttackVillage(Village &attacker, Village &defender);
void takePlayerTurn(Village &village, std::vector<Village> &villages);
void takeAITurn(Village &village);

////--------------------------------------------------------------------------------------------------------------------

#endif //MAIN_CPP_HEADER_H
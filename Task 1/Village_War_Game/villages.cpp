#include "header.h"

//// Villages

// Generates a vector of Village objects for the specified number of players and AIs
std::vector<Village> generateVillages(int numPlayers, int numAIs) {

    // Initialize empty vector of villages
    std::vector<Village> villages;

    // Create random number generator using std::random_device and std::mt19937
    std::random_device rd;
    std::mt19937 rng(rd());

// Generate the player's village(s)
    for (int i = 0; i < numPlayers; i++) {
        // Create a Village object
        Village playerVillage;
        // Set the isPlayer flag to true, indicating that this is a player village
        playerVillage.isPlayer = true;

        // Random number generator for x coordinate
        std::uniform_int_distribution<int> xDist(0, MAP_WIDTH - 1);
        // Generate a random x coordinate for the village
        playerVillage.x = xDist(rng);

        // Random number generator for y coordinate
        std::uniform_int_distribution<int> yDist(0, MAP_HEIGHT - 1);
        // Generate a random y coordinate for the village
        playerVillage.y = yDist(rng);

        // Set the resources of the village to 100 of each
        playerVillage.resources = {100, 100, 100};
        // Set initial health to 100
        playerVillage.health = 100;
        // Generate buildings for the village
        playerVillage.buildings = generateBuildings(playerVillage);
        // Generate troops for the village
        playerVillage.troops = generateTroops(playerVillage);
        // Add the village to the vector
        villages.push_back(playerVillage);
    }

    // Generate the AI villages
    for (int i = 0; i < numAIs; i++) {
        Village aiVillage;
        aiVillage.isPlayer = false;

        // Distribution for generating random x-coordinate
        std::uniform_int_distribution<int> xDist2(0, MAP_WIDTH - 1);
        // Generate random x-coordinate
        aiVillage.x = xDist2(rng);

        // Distribution for generating random y-coordinate
        std::uniform_int_distribution<int> yDist2(0, MAP_HEIGHT - 1);
        // Generate random y-coordinate
        aiVillage.y = yDist2(rng);

        // Set the resources of the AI village to 100 of each
        aiVillage.resources = {100, 100, 100};
        // Set initial health to 100
        aiVillage.health = 100;
        // Generate buildings for the AI village
        aiVillage.buildings = generateBuildings(aiVillage);
        // Generate troops for the AI village
        aiVillage.troops = generateTroops(aiVillage);
        // Add the AI village to the vector
        villages.push_back(aiVillage);
    }

    return villages;
}

////--------------------------------------------------------------------------------------------------------------------

// Outputs information about every village
void villages_info(const std::vector<Village> &newVillages) {
    for (const Village &village: newVillages) {
        // Print village type (player or AI)
        std::cout << "\n";
        std::cout << "Village: ";
        if (village.isPlayer) {
            std::cout << "Player's village" << std::endl;
        } else {
            std::cout << "AI's village" << std::endl;
        }
        // Print village health
        std::cout << " Health: " << village.health << std::endl;

        // Print village resources
        std::cout << " Resources: " << std::endl;
        std::cout << " Wood: " << village.resources.wood << std::endl;
        std::cout << " Gold: " << village.resources.gold << std::endl;
        std::cout << " Food: " << village.resources.food << std::endl;

        // Print village buildings
        std::cout << " Buildings:" << std::endl;
        for (const Building &building: village.buildings) {
            std::cout << " " << building.name << " (Level " << building.level << ")" << std::endl;
        }

        // Print village troops
        std::cout << " Troops:" << std::endl;
        for (const Troop &troop: village.troops) {
            std::cout << " Type: " << troop.type << " Attack: " << troop.attack << " Defense: "
                      << troop.defense << " Health: " << troop.health << std::endl;
        }
    }
}
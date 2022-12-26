#include "header.h"

//// Villages
// Generates a vector of Village objects for the specified number of players and AIs

std::vector<Village> generateVillages(int numPlayers, int numAIs) {

    std::vector<Village> villages;

    std::random_device rd;
    std::mt19937 rng(rd());

    // Generate the player's village(s)
    for (int i = 0; i < numPlayers; i++) {
        Village playerVillage;
        playerVillage.isPlayer = true;

        std::uniform_int_distribution<int> xDist(0, MAP_WIDTH - 1);
        playerVillage.x = xDist(rng);

        std::uniform_int_distribution<int> yDist(0, MAP_HEIGHT - 1);
        playerVillage.y = yDist(rng);

        playerVillage.resources = {100, 100, 100};
        playerVillage.health = 100;
        playerVillage.buildings = generateBuildings(playerVillage);
        playerVillage.troops = generateTroops(playerVillage);
        villages.push_back(playerVillage);
    }

    // Generate the AI villages
    for (int i = 0; i < numAIs; i++) {
        Village aiVillage;
        aiVillage.isPlayer = false;

        std::uniform_int_distribution<int> xDist2(0, MAP_WIDTH - 1);
        aiVillage.x = xDist2(rng);

        std::uniform_int_distribution<int> yDist2(0, MAP_HEIGHT - 1);
        aiVillage.y = yDist2(rng);

        aiVillage.resources = {100, 100, 100};
        aiVillage.health = 100;
        aiVillage.buildings = generateBuildings(aiVillage);
        aiVillage.troops = generateTroops(aiVillage);
        villages.push_back(aiVillage);
    }

    return villages;
}
////--------------------------------------------------------------------------------------------------------------------

// Outputs information about every village
void villages_info(const std::vector<Village> &newVillages) {
// Output information about each village
    for (const Village &village: newVillages) {
        std::cout << "\n";
        std::cout << "Village: ";
        if (village.isPlayer) {
            std::cout << "Player's village" << std::endl;
        } else {
            std::cout << "AI's village" << std::endl;
        }
        std::cout << " Health: " << village.health << std::endl;
        std::cout << " Resources: " << std::endl;
        std::cout << " Wood: " << village.resources.wood << std::endl;
        std::cout << " Gold: " << village.resources.gold << std::endl;
        std::cout << " Food: " << village.resources.food << std::endl;
        std::cout << " Buildings:" << std::endl;
        for (const Building &building: village.buildings) {
            std::cout << " " << building.name << " (Level " << building.level << ")" << std::endl;
        }
        std::cout << " Troops:" << std::endl;
        for (const Troop &troop: village.troops) {
            std::cout << " Type: " << troop.type << " Attack: " << troop.attack << " Defense: "
                      << troop.defense << " Health: " << troop.health << std::endl;
        }
    }
}
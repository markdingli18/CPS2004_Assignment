#include <iostream>
#include <vector>
#include <cstdlib> // for std::rand
#include <ctime> // for std::time

#define MAP_HEIGHT 50
#define MAP_WIDTH 50

////--------------------------------------------------------------------------------------------------------------------

//// Variables
int numPlayers;
int numAIs;
int swordsmanCount = 0;
int archerCount = 0;
int cavalryCount = 0;
int AI_swordsmanCount = 0;
int AI_archerCount = 0;
int AI_cavalryCount = 0;

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
    int troopGenerationRate;
    Resources costToUpgrade;
};

struct Troop {
    std::string type; // Type of troop (e.g. "Sword", "Archer", "Cavalry")
    int attack;
    int defense;
    int health;
    int trainingCost;
    int carryingCapacity;
    int marchingSpeed;
};

struct Village {
    int x; // x coordinate of the village
    int y; // y coordinate of the village
    int health; // health of the village
    bool isPlayer; // flag to indicate whether the village belongs to the player or an AI
    std::vector<Building> buildings; // vector of buildings in the village
    std::vector<Troop> troops; // vector of troops in the village
    Resources resources;
    int id; // ID of the village
};

////--------------------------------------------------------------------------------------------------------------------

//// Map
// Generates Map
Map generateMap(int width, int height) {
    Map map;
    map.width = width;
    map.height = height;
    map.cells.resize(height);
    for (int y = 0; y < height; y++) {
        map.cells[y].resize(width);
        for (int x = 0; x < width; x++) {
            // Set the value of each cell to 0
            map.cells[y][x] = 0;
        }
    }
    return map;
}

// Print Map
void printMap(const Map& map, const std::vector<Village>& villages) {
    std::cout << "Game Map:\n" << std::endl;
    for (int y = 0; y < map.height; y++) {
        for (int x = 0; x < map.width; x++) {
            // Check if the current cell corresponds to the location of a village
            bool isVillage = false;
            for (const Village &village : villages) {
                if (village.x == x && village.y == y) {
                    isVillage = true;
                    break;
                }
            }

            // If the current cell is a village, output a 'V' character
            // Otherwise, output the value of the cell
            if (isVillage) {
                std::cout << "V" << " ";
            } else {
                std::cout << map.cells[y][x] << " ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "\n===================================================================================================" << std::endl;

}

//----------------------------------------------------------------------------------------------------------------------
//// Troops
// Generates a vector of Troop objects for the specified number of troops
std::vector<Troop> generateTroops(Village &village) {
    std::vector<Troop> troops;

    // Generate 3 types of troops
    for (int i = 0; i < 3; i++) {
        Troop troop;
        // Set the attack, defense, health, training cost, carrying capacity, and marching speed for the troop based on its type
        if (i == 0) {
            troop.type = "Swordsman";
            troop.attack = 10;
            troop.defense = 5;
            troop.health = 30;
            troop.trainingCost = 30;
            troop.carryingCapacity = 20;
            troop.marchingSpeed = 3;
        } else if (i == 1) {
            troop.type = "Archer";
            troop.attack = 5;
            troop.defense = 10;
            troop.health = 20;
            troop.trainingCost = 20;
            troop.carryingCapacity = 10;
            troop.marchingSpeed = 5;
        } else {
            troop.type = "Cavalry";
            troop.attack = 12;
            troop.defense = 7;
            troop.health = 35;
            troop.trainingCost = 40;
            troop.carryingCapacity = 25;
            troop.marchingSpeed = 4;
        }
        troops.push_back(troop);
    }

    return troops;
}

//----------------------------------------------------------------------------------------------------------------------
//// Buildings
std::vector<Building> generateBuildings(Village &village) {
    std::vector<Building> buildings;

    // Generate 3 resource-generating buildings
    for (int i = 0; i < 3; i++) {
        Building building;
        building.type = "ResourceGenerator";
        building.level = 1;
        // Set the name and resource generation rate for the building based on its type
        if (i == 0) {
            building.name = "Gold Mine";
            building.resourceGenerationRate = 50;
            building.costToUpgrade = {100, 50, 30};
        } else if (i == 1) {
            building.name = "Lumber Mill";
            building.resourceGenerationRate = 150;
            building.costToUpgrade = {80, 40, 30};
        } else {
            building.name = "Farm";
            building.resourceGenerationRate = 100;
            building.costToUpgrade = {80, 30, 40};
        }
        buildings.push_back(building);
    }

    // Generate 3 troop-generating buildings
    for (int i = 0; i < 3; i++) {
        Building building;
        building.type = "TroopGenerator";
        building.level = 1;
        // Set the name, troop generation cost, and training time for the building based on its type
        if (i == 0) {
            building.name = "Barracks";
            building.troopGenerationCost = 50;
            building.costToUpgrade = {200, 100, 60};
        } else if (i == 1) {
            building.name = "Archery Range";
            building.troopGenerationCost = 40;
            building.costToUpgrade = {160, 80, 40};
        } else {
            building.name = "Stables";
            building.troopGenerationCost = 60;
            building.costToUpgrade = {120, 60, 30};
        }
        buildings.push_back(building);
    }

    return buildings;
}

// Upgrade Buildings with resources Function
bool upgradeBuilding(Village &village, Building &building) {
    // Check if the village has enough resources to upgrade the building
    if (village.resources.wood >= building.costToUpgrade.wood &&
        village.resources.gold >= building.costToUpgrade.gold &&
        village.resources.food >= building.costToUpgrade.food) {
        // Deduct the upgrade cost from the village's resources
        village.resources.wood -= building.costToUpgrade.wood;
        village.resources.gold -= building.costToUpgrade.gold;
        village.resources.food -= building.costToUpgrade.food;
        // Increase the building's level
        building.level++;
        // Update the resource generation rate and troop generation cost/training time based on the new level
        if (building.type == "ResourceGenerator") {
            building.resourceGenerationRate += 10;
        } else {
            building.troopGenerationCost += 20;
        }
        // Increase the cost to upgrade the building
        building.costToUpgrade.wood += 20;
        building.costToUpgrade.gold += 10;
        building.costToUpgrade.food += 5;
        return true;
    }
    return false;
}

//----------------------------------------------------------------------------------------------------------------------
// Generates a vector of Village objects for the specified number of players and AIs
std::vector<Village> generateVillages(int numPlayers, int numAIs) {
    std::vector<Village> villages;

    // Generate the player's village
    Village playerVillage;
    playerVillage.isPlayer = true;
    playerVillage.x = rand() % MAP_WIDTH;  // Generate a random x coordinate between 0 and MAP_WIDTH-1
    playerVillage.y = rand() % MAP_HEIGHT; // Generate a random y coordinate between 0 and MAP_HEIGHT-1
    playerVillage.resources = {100, 100, 100};
    playerVillage.health = 100;
    playerVillage.buildings = generateBuildings(playerVillage);
    playerVillage.troops = generateTroops(playerVillage);
    playerVillage.id = 0;
    villages.push_back(playerVillage);

    // Generate the AI villages
    for (int i = 0; i < numAIs; i++) {
        Village aiVillage;
        aiVillage.isPlayer = false;
        aiVillage.x = rand() % MAP_WIDTH;  // Generate a random x coordinate between 0 and MAP_WIDTH-1
        aiVillage.y = rand() % MAP_HEIGHT; // Generate a random y coordinate between 0 and MAP_HEIGHT-1
        aiVillage.resources = {100, 100, 100};
        aiVillage.health = 100;
        aiVillage.buildings = generateBuildings(aiVillage);
        aiVillage.troops = generateTroops(aiVillage);
        aiVillage.id = i + 1; // Assign unique ID to each AI village
        villages.push_back(aiVillage);
    }

    return villages;
}
////--------------------------------------------------------------------------------------------------------------------

////Functions
// Return true if the user wants to continue playing, false otherwise
bool gameIsRunning() {
    // Prompt the user to continue or quit
    std::cout << "\n=======================================================================\n"<< std::endl;
    std::cout << "\t   Enter Q to quit or any other key to continue: ";
    char input;
    std::cin >> input;
    std::cout << "\n=======================================================================\n" << std::endl;
    if (input == 'Q' || input == 'q') {
        std::cout << "\n=======================================================================\n" << std::endl;
        std::cout << "\t\t\tQUITTING THE GAME...\n";
        std::cout << "\n=======================================================================\n" << std::endl;
        return false;
    }
    return true;
}

//------------------------------------------------------------------------------------------------------------------

bool winGame(std::vector<Village> &villages) {
    // Check if the player's village has run out of health
    if (villages[0].health == 0) {
        std::cout << "\n=======================================================================\n" << std::endl;
        std::cout << "\t\tYOUR VILLAGE WAS DESTROYED!\n\t\t\tYOU LOST!." << std::endl;
        return true;
    }

    // Check if all the AI villages have run out of health
    bool allAIVillagesLost = true;
    for (int i = 1; i < villages.size(); i++) {
        if (villages[i].health > 0) {
            allAIVillagesLost = false;
            break;
        }
    }
    if (allAIVillagesLost) {
        std::cout << "\n=======================================================================\n" << std::endl;
        std::cout << "\t\tALL AI VILLAGES DESTROYED!\n\t\t\tYOU WIN!." << std::endl;
        return true;
    }

    return false;
}

//------------------------------------------------------------------------------------------------------------------

// Function for resource generation
void generateResources(Village &village) {
    // Iterate over the village's buildings
    for (int i = 0; i < village.buildings.size(); i++) {
        Building &building = village.buildings[i];
        // If the building is a resource generator, update the village's resources
        if (building.type == "ResourceGenerator") {
            if (building.name == "Lumber Mill") {
                village.resources.wood += building.resourceGenerationRate + 40 * (building.level - 1);
            } else if (building.name == "Gold Mine") {
                village.resources.gold += building.resourceGenerationRate + 20 * (building.level - 1);
            } else if (building.name == "Farm") {
                village.resources.food += building.resourceGenerationRate + 30 * (building.level - 1);
            }
        }
    }
}
//------------------------------------------------------------------------------------------------------------------

void attackVillage(Village &attackingVillage, Village &defendingVillage) {
    // Create a vector to store the selected troops
    std::vector<Troop> selectedTroops;

    std::cout << "\n=======================================================================\n"<< std::endl;
    std::cout << "Number of Swordsmen: " << swordsmanCount << std::endl;
    std::cout << "Number of Archers: " << archerCount << std::endl;
    std::cout << "Number of Cavalry: " << cavalryCount << std::endl;
    std::cout << "\n"<< std::endl;

    // Prompt the player to select troops
    std::cout << "Enter the number of Swordsmen you want to send: ";
    int numSwordsmen;
    std::cin >> numSwordsmen;
    for (int i = 0; i < numSwordsmen; i++) {
        // Find a Swordsmen troop to send
        bool foundTroop = false;
        for (size_t j = 0; j < attackingVillage.troops.size(); j++) {
            if (attackingVillage.troops[j].type == "Swordsman") {
                selectedTroops.push_back(attackingVillage.troops[j]);
                attackingVillage.troops.erase(attackingVillage.troops.begin() + j);
                foundTroop = true;
                break;
            }
        }
        if (!foundTroop) {
            std::cout << "You don't have any more Swordsmen available.\n";
            break;
        }
    }

    // Prompt the player to select troops
    std::cout << "Enter the number of Archers you want to send: ";
    int numArcher;
    std::cin >> numArcher;
    for (int i = 0; i < numArcher; i++) {
        // Find an Archer troop to send
        bool foundTroop = false;
        for (size_t j = 0; j < attackingVillage.troops.size(); j++) {
            if (attackingVillage.troops[j].type == "Archer") {
                selectedTroops.push_back(attackingVillage.troops[j]);
                attackingVillage.troops.erase(attackingVillage.troops.begin() + j);
                foundTroop = true;
                break;
            }
        }
        if (!foundTroop) {
            std::cout << "You don't have any more Archers available.\n";
            break;
        }
    }

    // Prompt the player to select troops
    std::cout << "Enter the number of Cavalry you want to send: ";
    int numCavalry;
    std::cin >> numCavalry;
    for (int i = 0; i < numCavalry; i++) {
        // Find a Cavalry troop to send
        bool foundTroop = false;
        for (size_t j = 0; j < attackingVillage.troops.size(); j++) {
            if (attackingVillage.troops[j].type == "Cavalry") {
                selectedTroops.push_back(attackingVillage.troops[j]);
                attackingVillage.troops.erase(attackingVillage.troops.begin() + j);
                foundTroop = true;
                break;
            }
        }
        if (!foundTroop) {
            std::cout << "You don't have any more Cavalry available.\n";
            break;
        }
    }

    // Sum the attack of the selected troops
    int attackingVillageAttack = 0;
    for (const Troop &troop: selectedTroops) {
        attackingVillageAttack += troop.attack;
    }

    // Sum the attack of the troops in the defending army
    int defendingVillageAttack = 0;
    for (const Troop &troop: defendingVillage.troops) {
        defendingVillageAttack += troop.attack;
    }

    // Kill troops from both armies until the total health of the killed troops is equal to the opposing army's attack
    while (attackingVillageAttack > 0 && defendingVillageAttack > 0) {
        // Choose a random troop from the attacking village to kill
        int troopIndex = std::rand() % selectedTroops.size();
        Troop &troop = selectedTroops[troopIndex];
        attackingVillageAttack -= troop.health;
        selectedTroops.erase(selectedTroops.begin() + troopIndex);

        // Choose a random troop from the defending village to kill
        troopIndex = std::rand() % defendingVillage.troops.size();
        troop = defendingVillage.troops[troopIndex];
        defendingVillageAttack -= troop.health;
        defendingVillage.troops.erase(defendingVillage.troops.begin() + troopIndex);
    }

    // Check if the attack was successful
    if (!selectedTroops.empty()) {
        // Calculate the total attack of the surviving troops
        int totalAttack = 0;
        for (const Troop &troop: selectedTroops) {
            totalAttack += troop.attack;
        }

        // Deal damage to the defending village
        defendingVillage.health -= totalAttack;

        // Calculate the carrying capacity of the surviving troops
        int carryingCapacity = 0;
        for (const Troop &troop: selectedTroops) {
            carryingCapacity += troop.carryingCapacity;
        }

        // Reduce resources from the defending village
        defendingVillage.resources.food -= carryingCapacity;
        defendingVillage.resources.wood -= carryingCapacity;
        defendingVillage.resources.gold -= carryingCapacity;

        std::cout << "\nThe defending village took " << totalAttack << " damage and lost " << carryingCapacity << " resources." << std::endl;
    }
    else {
        std::cout << "\n=======================================================================\n" << std::endl;
        std::cout << "The attack was unsuccessful.\n" << std::endl;
    }

    // Output the health of the defending village after the attack
    std::cout << "\nThe defending village's health is now: " << defendingVillage.health << std::endl;

}

//------------------------------------------------------------------------------------------------------------------

void aiAttackVillage(Village &attacker, Village &defender) {
    // Seed the random number generator with the current time
    std::srand(std::time(nullptr));
    // Generate random numbers for the number of troops the AI will use in the attack
    int swordsmen = std::rand() % attacker.troops.size();
    int archers = std::rand() % attacker.troops.size();
    int cavalry = std::rand() % attacker.troops.size();

    // Make sure the AI is using at least one troop in the attack
    if (swordsmen == 0 && archers == 0 && cavalry == 0) {
        // Choose a random troop type to use in the attack
        int troopType = std::rand() % 3 + 1;
        if (troopType == 1) {
            swordsmen = 1;
        } else if (troopType == 2) {
            archers = 1;
        } else {
            cavalry = 1;
        }
    }

    // Create a vector to store the selected troops
    std::vector<Troop> selectedTroops;

    // Select the specified number of troops
    for (int i = 0; i < swordsmen; i++) {
        // Find a Swordsmen troop to send
        bool foundTroop = false;
        for (size_t j = 0; j < attacker.troops.size(); j++) {
            if (attacker.troops[j].type == "Swordsman") {
                selectedTroops.push_back(attacker.troops[j]);
                attacker.troops.erase(attacker.troops.begin() + j);
                foundTroop = true;
                break;
            }
        }
        if (!foundTroop) {
            break;
        }
    }
    for (int i = 0; i < swordsmen; i++) {
        // Find a Swordsmen troop to send
        bool foundTroop = false;
        for (size_t j = 0; j < attacker.troops.size(); j++) {
            if (attacker.troops[j].type == "Swordsman") {
                selectedTroops.push_back(attacker.troops[j]);
                attacker.troops.erase(attacker.troops.begin() + j);
                foundTroop = true;
                break;
            }
        }
        if (!foundTroop) {
            break;
        }
    }

    for (int i = 0; i < archers; i++) {
        // Find an Archer troop to send
        bool foundTroop = false;
        for (size_t j = 0; j < attacker.troops.size(); j++) {
            if (attacker.troops[j].type == "Archer") {
                selectedTroops.push_back(attacker.troops[j]);
                attacker.troops.erase(attacker.troops.begin() + j);
                foundTroop = true;
                break;
            }
        }
        if (!foundTroop) {
            break;
        }
    }

    for (int i = 0; i < cavalry; i++) {
        // Find a Cavalry troop to send
        bool foundTroop = false;
        for (size_t j = 0; j < attacker.troops.size(); j++) {
            if (attacker.troops[j].type == "Cavalry") {
                selectedTroops.push_back(attacker.troops[j]);
                attacker.troops.erase(attacker.troops.begin() + j);
                foundTroop = true;
                break;
            }
        }
        if (!foundTroop) {
            break;
        }
    }

    // Sum the attack of the selected troops
    int attackingVillageAttack = 0;
    for (const Troop &troop: selectedTroops) {
        attackingVillageAttack += troop.attack;
    }

    // Sum the attack of the troops in the defending army
    int defendingVillageAttack = 0;
    for (const Troop &troop: defender.troops) {
        defendingVillageAttack += troop.attack;
    }

    // Kill troops from both armies until the total health of the killed troops is equal to the opposing army's attack
    while (attackingVillageAttack > 0 && defendingVillageAttack > 0) {
        // Choose a random troop from the attacking village to kill
        int troopIndex = std::rand() % selectedTroops.size();
        Troop &troop = selectedTroops[troopIndex];
        attackingVillageAttack -= troop.health;
        selectedTroops.erase(selectedTroops.begin() + troopIndex);

        // Choose a random troop from the defending village to kill
        troopIndex = std::rand() % defender.troops.size();
        troop = defender.troops[troopIndex];
        defendingVillageAttack -= troop.health;
        defender.troops.erase(defender.troops.begin() + troopIndex);
    }

    // Check if the attack was successful
    if (!selectedTroops.empty()) {
        // Calculate the total attack of the surviving troops
        int totalAttack = 0;
        for (const Troop &troop: selectedTroops) {
            totalAttack += troop.attack;
        }

        // Deal damage to the defending village
        defender.health -= totalAttack;

        // Calculate the carrying capacity of the surviving troops
        int carryingCapacity = 0;
        for (const Troop &troop: selectedTroops) {
            carryingCapacity += troop.carryingCapacity;
        }

        // Reduce resources from the defending village
        defender.resources.food -= carryingCapacity;
        defender.resources.wood -= carryingCapacity;
        defender.resources.gold -= carryingCapacity;

        std::cout << "\nThe defending village took " << totalAttack << " damage and lost " << carryingCapacity << " resources." << std::endl;
    }
    else {
        std::cout << "\n=======================================================================\n" << std::endl;
        std::cout << "The attack by the AI was unsuccessful.\n" << std::endl;
    }

    // Output the health of the defending village after the attack
    std::cout << "\nThe defending village's health is now: " << defender.health << std::endl;
}

//------------------------------------------------------------------------------------------------------------------

// Player action for turn Phase (menu)
void doPlayerActions(Village& village, std::vector<Village> &villages) {
    // Display the available resources and a list of actions the player can take
    std::cout << "\tREMAINING RESOURCES: wood - " << village.resources.wood << ", gold - " << village.resources.gold
              << ", food - " << village.resources.food << std::endl;
    std::cout << "\n=======================================================================\n" << std::endl;
    std::cout
            << "ACTIONS: \n1. Build/upgrade buildings\n2. Train troops\n3. Attack another village\n4. Surrender\n5. Pass the turn\n\nEnter the number of the action you want to take: ";
    // Read in the player's action
    int action;
    std::cin >> action;

    std::cout << "\n=======================================================================\n" << std::endl;

    // TODO CHECK FOR TROOP
    /*// Check if the player has any troops to attack with
    bool hasTroops = false;
    for (const Troop &troop: village.troops) {
        if ((troop.type == "Swordsman") || (troop.type == "Archer") || (troop.type == "Cavalry")) {
            hasTroops = true;
            break;
        }
    }

    // If the player doesn't have any troops, and they try to choose action 3, ask them to choose a different action
    if (action == 3 && !hasTroops) {
        std::cout << "You don't have any troops to attack with. Please choose a different action.\n" << std::endl;
        doPlayerActions(village, villages);
        return;
    }*/

    // Perform the selected action
    if (action == 1) {
        while (true) {
            std::cout << "Buildings: " << std::endl;
            int i = 1;
            for (auto &building: village.buildings) {
                std::cout << i << ". " << building.name << " (level " << building.level << ")" << std::endl;
                // Display Cost to Upgrade
                std::cout << "Cost to upgrade: " << building.costToUpgrade.wood << " Wood, "
                          << building.costToUpgrade.gold << " Gold, " << building.costToUpgrade.food << " Food\n"
                          << std::endl;
                i++;
            }
            std::cout << "Enter the number of the building you want to upgrade (or 0 to cancel): ";
            int buildingIndex;
            std::cin >> buildingIndex;
            if (buildingIndex == 0) {
                // Cancel the action
                doPlayerActions(village, villages);
            } else if (buildingIndex > 0 && buildingIndex <= village.buildings.size()) {
                // Valid building selected
                Building &building = village.buildings[buildingIndex - 1];
                // Upgrade the building
                if (upgradeBuilding(village, building)) {
                    std::cout << "\n=======================================================================\n"
                              << std::endl;
                    std::cout << "\t\t " << building.name << " upgraded to level " << building.level << "!"
                              << std::endl;
                    std::cout << "\n\tREMAINING RESOURCES: wood = " << village.resources.wood << ", gold - "
                              << village.resources.gold
                              << ", food - " << village.resources.food << std::endl;
                    break;
                } else {
                    std::cout << "\n=======================================================================\n"
                              << std::endl;
                    std::cout << "You don't have enough resources to upgrade this building. Want to choose another?"
                              << std::endl;
                    std::cout << "\n=======================================================================\n"
                              << std::endl;
                }
            }
        }
    } else if (action == 2) {
        // Code for training troops goes here
        while (true) {
            std::cout << "Troops: " << std::endl;
            int i = 1;
            for (auto &troop: village.troops) {
                std::cout << i << ". " << troop.type << " (" << troop.trainingCost << " from all Resources)"
                          << std::endl;
                i++;
            }
            std::cout << "\nEnter the number of the troop you want to train (or 0 to cancel): ";
            int troopIndex;
            std::cin >> troopIndex;
            if (troopIndex == 0) {
                // Cancel the training
                doPlayerActions(village, villages);
            } else if (troopIndex > 0 && troopIndex <= village.troops.size()) {
                // Valid troop selected
                Troop &troop = village.troops[troopIndex - 1];

                // Determine how many troops to generate based on building levels
                int numTroopsToGenerate = 1;  // default to 1 troop
                for (auto &building: village.buildings) {
                    if (building.name == "Barracks" && troop.type == "Swordsman") {
                        numTroopsToGenerate = building.level;  // use the level of the Barracks building to determine how many troops to generate
                    } else if (building.name == "Archery Range" && troop.type == "Archer") {
                        numTroopsToGenerate = building.level;  // use the level of the Archery Range building to determine how many troops to generate
                    } else if (building.name == "Stables" && troop.type == "Cavalry") {
                        numTroopsToGenerate = building.level;  // use the level of the Stables building to determine how many troops to generate
                    }
                }

                // Check if the player has enough resources to train the troop
                if (village.resources.wood >= troop.trainingCost * numTroopsToGenerate
                    && village.resources.gold >= troop.trainingCost * numTroopsToGenerate
                    && village.resources.food >= troop.trainingCost * numTroopsToGenerate) {
                    // Train the troops
                    village.resources.wood -= troop.trainingCost * numTroopsToGenerate;
                    village.resources.gold -= troop.trainingCost * numTroopsToGenerate;
                    village.resources.food -= troop.trainingCost * numTroopsToGenerate;
                    std::cout << "\n=======================================================================\n"
                              << std::endl;
                    std::cout << "\t\t\t" << numTroopsToGenerate << " " << troop.type << " trained!" << std::endl;

                    if (troop.type == "Swordsman") {
                        swordsmanCount += numTroopsToGenerate;
                    } else if (troop.type == "Archer") {
                        archerCount += numTroopsToGenerate;
                    } else if (troop.type == "Cavalry") {
                        cavalryCount += numTroopsToGenerate;
                    }

                    std::cout << "\n=======================================================================\n"<< std::endl;
                    std::cout << "Number of Swordsmen: " << swordsmanCount << std::endl;
                    std::cout << "Number of Archers: " << archerCount << std::endl;
                    std::cout << "Number of Cavalry: " << cavalryCount << std::endl;

                    break;
                } else {
                    std::cout << "\n=======================================================================\n"
                              << std::endl;
                    std::cout << "You don't have enough resources to train this troop." << std::endl;
                    std::cout << "\n=======================================================================\n"
                              << std::endl;
                }
            } else {
                // Invalid troop selected
                std::cout << "\n=======================================================================\n" << std::endl;
                std::cout << "Invalid troop selected. Please try again." << std::endl;
            }
        }
        std::cout << "\n\tREMAINING RESOURCES: Wood - " << village.resources.wood << ", Gold - "
                  << village.resources.gold
                  << ", Food - " << village.resources.food << std::endl;

    } else if (action == 3) {

        // Output the list of villages and whether they belong to the player or an AI
        for (int i = 0; i < villages.size(); i++) {
            const Village &village = villages[i];
            std::cout << i << ": " << (village.isPlayer ? "Player" : "AI") << std::endl;
        }

        // Choose the village to attack
        int villageIndex;
        std::cout << "Enter the index of the village you want to attack: ";
        std::cin >> villageIndex;

        // TODO fix infinite loop
        // Wrap the checks in a loop
        for (;;) {
            // Make sure the index is valid
            if (villageIndex < 0 || villageIndex >= villages.size() || villageIndex == 0) {
                std::cout << "Error: Invalid village index" << std::endl;
                continue;
            }

            Village &defendingVillage = villages[villageIndex];

            // Make sure the attacking village has at least one troop
            if (village.troops.empty()) {
                std::cout << "Error: You don't have any troops to attack with" << std::endl;
                continue;
            }

            // Make sure the defending village is not the player's own village
            if (defendingVillage.isPlayer) {
                std::cout << "Error: You can't attack your own village" << std::endl;
                continue;
            }

            // Call the attackVillage function
            attackVillage(village, defendingVillage);
            // Exit the loop if no errors were encountered
            break;
        }

    } else if (action == 4) {
        // Surrender
        // Set the village's health to 0
        village.health = 0;
        std::cout << "\n=======================================================================\n" << std::endl;
        std::cout << "\tYOU HAVE SURRENDERED! YOUR VILLAGE HAS BEEN DESTROYED!" << std::endl;
        std::cout << "\n=======================================================================\n" << std::endl;
        exit(0);  // exit the game
    } else if (action == 5) {
        // Code for passing the turn goes here
        std::cout << "\n=======================================================================\n" << std::endl;
        std::cout << "\t\t   Player has passed the turn." << std::endl;
        std::cout << "\n=======================================================================\n" << std::endl;
    } else {
        // Invalid action
        std::cout << "\n=======================================================================\n" << std::endl;
        std::cout << "\t\t  Invalid action. Please try again." << std::endl;
        std::cout << "\n=======================================================================\n" << std::endl;
        doPlayerActions(village, villages);
    }
}

//------------------------------------------------------------------------------------------------------------------

void doAIActions(Village& village) {
    // Seed the random number generator with the current time
    std::srand(std::time(nullptr));

    bool actionSuccessful = false;
    while (!actionSuccessful) {
        // Generate a random number between 1 and 4
        int AI_action = std::rand() % 4 + 1;
        std::cout << "\n=======================================================================\n" << std::endl;
        std::cout << "\n\t\t\tAI chose action: " << AI_action << std::endl;

        // Perform the selected action
        if (AI_action == 1) {
            // Choose a random building to upgrade
            if (!village.buildings.empty()) {
                int buildingIndex = std::rand() % village.buildings.size();
                Building &building = village.buildings[buildingIndex];
                // Check if the AI has enough resources to upgrade the building
                if (upgradeBuilding(village, building)) {
                    std::cout << "\n=======================================================================\n"
                              << std::endl;
                    std::cout << "\n\t\tAI upgraded " << building.name << " to level " << building.level << "!"
                              << std::endl;
                    actionSuccessful = true;
                }
            }
        } else if (AI_action == 2) {
            // Code for training troops goes here
            if (!village.troops.empty()) {
                bool enoughResources = false;
                while (!enoughResources) {
                    // Choose a random troop to train
                    int troopIndex = std::rand() % village.troops.size();
                    Troop &troop = village.troops[troopIndex];
                    // Check if the AI has enough resources to train the troop
                    if (village.resources.wood >= troop.trainingCost &&
                        village.resources.gold >= troop.trainingCost
                        && village.resources.food >= troop.trainingCost) {
                        // Train the troop
                        village.resources.wood -= troop.trainingCost;
                        village.resources.gold -= troop.trainingCost;
                        village.resources.food -= troop.trainingCost;
                        std::cout << "\n=======================================================================\n"
                                  << std::endl;
                        std::cout << "\n\t\t\tAI trained " << troop.type << "!" << std::endl;
                        enoughResources = true;
                        if (troop.type == "Swordsman") {
                            AI_swordsmanCount++;
                        } else if (troop.type == "Archer") {
                            AI_archerCount++;
                        } else if (troop.type == "Cavalry") {
                            AI_cavalryCount++;
                        }

                        actionSuccessful = true;
                    }
                    else {
                        // Choose another troop to train
                        bool enoughResources = false;
                        while (!enoughResources) {
                            // Generate a new random number between 1 and the number of troops
                            int newTroopIndex = std::rand() % village.troops.size();
                            // Make sure we choose a different troop than the original one
                            while (newTroopIndex == troopIndex) {
                                newTroopIndex = std::rand() % village.troops.size();
                            }
                            Troop &newTroop = village.troops[newTroopIndex];
                            if (village.resources.wood >= newTroop.trainingCost &&
                                village.resources.gold >= newTroop.trainingCost
                                && village.resources.food >= newTroop.trainingCost) {
                                // Train the new troop
                                village.resources.wood -= newTroop.trainingCost;
                                village.resources.gold -= newTroop.trainingCost;
                                village.resources.food -= newTroop.trainingCost;
                                std::cout << "\n=======================================================================\n"
                                          << std::endl;
                                std::cout << "\n\t\tAI trained " << newTroop.type << "!" << std::endl;
                                enoughResources = true;
                                actionSuccessful = true;
                                if (newTroop.type == "Swordsman") {
                                    AI_swordsmanCount++;
                                } else if (newTroop.type == "Archer") {
                                    AI_archerCount++;
                                } else if (newTroop.type == "Cavalry") {
                                    AI_cavalryCount++;
                                }
                            }
                        }
                    }
                }
            }
        } else if (AI_action == 3) {

            // TODO: Code for attacking another village goes here
            aiAttackVillage(village, village);

        } else if (AI_action == 4) {
            // Check if the AI has enough resources to perform any of the other actions
            bool actionSuccessful = false;
            if (!village.buildings.empty()) {
                int buildingIndex = std::rand() % village.buildings.size();
                Building &building = village.buildings[buildingIndex];
                if (upgradeBuilding(village, building)) {
                    actionSuccessful = true;
                }
            }
            if (!actionSuccessful && !village.troops.empty()) {
                int troopIndex = std::rand() % village.troops.size();
                Troop &troop = village.troops[troopIndex];
                if (village.resources.wood >= troop.trainingCost &&
                    village.resources.gold >= troop.trainingCost
                    && village.resources.food >= troop.trainingCost) {
                    actionSuccessful = true;
                }
            }

            // If the AI doesn't have enough resources to perform any of the other actions, pass the turn
            if (!actionSuccessful) {
                // Code for passing the turn goes here
                std::cout << "\n=======================================================================" << std::endl;
                std::cout << "\n\t\t    AI passed the turn." << std::endl;
                std::cout << "\n=======================================================================\n" << std::endl;
            }
        }
    }
}

//------------------------------------------------------------------------------------------------------------------

void takePlayerTurn(Village &village, std::vector<Village> &villages) {
    // Player's turn
    std::cout << "\n=======================================================================\n"<< std::endl;
    std::cout << "\t\t\tPlayer's turn....\n" << std::endl;
    doPlayerActions(village, villages);
}

void takeAITurn(Village &village) {
    // AI's turn
    if (village.health > 0) {  // only perform actions if the village is still standing
        std::cout << "\n=======================================================================\n"<< std::endl;
        std::cout << "\t\t\t   AI's turn...." << std::endl;
        std::cout << "\n=======================================================================\n"<< std::endl;
        doAIActions(village);
    }
}

//------------------------------------------------------------------------------------------------------------------

int main() {

    //// Welcome Message
    // Display the top border
    std::cout << "=======================================================================\n" << std::endl;
    std::cout << "     /\\                                                        /\\\n"
                 "    |  |                                                      |  |\n"
                 "   /----\\                  Village War Game                  /----\\\n"
                 "  [______]                                                  [______]\n"
                 "   |    |         _____                        _____         |    |\n"
                 "   |[]  |        [     ]                      [     ]        |  []|\n"
                 "   |    |       [_______][ ][ ][ ][][ ][ ][ ][_______]       |    |\n"
                 "   |    [ ][ ][ ]|     |  ,----------------,  |     |[ ][ ][ ]    |\n"
                 "   |             |     |/'    ____..____    '\\|     |             |\n"
                 "    \\  []        |     |    /'    ||    '\\    |     |        []  /\n"
                 "     |      []   |     |   |o     ||     o|   |     |  []       |\n"
                 "     |           |  _  |   |     _||_     |   |  _  |           |\n"
                 "     |   []      | (_) |   |    (_||_)    |   | (_) |       []  |\n"
                 "     |           |     |   |     (||)     |   |     |           |\n"
                 "     |           |     |   |      ||      |   |     |           |\n"
                 "   /''           |     |   |o     ||     o|   |     |           ''\\\n"
                 "  [_____________[_______]--'------''------'--[_______]_____________]\n" << std::endl;
    std::cout << "=======================================================================\n" << std::endl;
    // Display the welcome message
    std::cout << "\t\t     WELCOME TO VILLAGE WAR!" << std::endl;
    std::cout << "ASSEMBLE YOUR TROOPS AND DEFEND YOUR VILLAGE FROM INVADING FORCES!" << std::endl;
    std::cout << "\t\tMAY THE GODS BE WITH YOU IN BATTLE.\n" << std::endl;
    // Display the bottom border
    std::cout << "=======================================================================\n" << std::endl;

    //------------------------------------------------------------------------------------------------------------------

    // Asking for user input and error checking
    while (true) {
        std::cout << "Enter the number of players (at least one): ";
        std::cin >> numPlayers;
        std::cout << "\n=======================================================================\n" << std::endl;

        // Check if the number of players is valid (at least one player)
        if (numPlayers > 0) {
            break;  // Valid input, exit the loop
        }

        // Invalid input, display an error message and continue the loop
        std::cout << "Error: The number of players must be at least one." << std::endl;
        std::cout << "\n=======================================================================\n" << std::endl;
    }

    while (true) {
        std::cout << "Enter the number of AIs (zero or more): ";
        std::cin >> numAIs;
        std::cout << "\n=======================================================================\n" << std::endl;
        if (numAIs >= 0) {
            break;
        }
        std::cout << "Error: Invalid number of AIs" << std::endl;
        std::cout << "\n=======================================================================\n" << std::endl;
    }

    Village village;
    //village.resources = {100, 100, 100}; // Initialize the village's resources

    std::vector<Village> villages = generateVillages(numPlayers, numAIs);

    // Print the coordinates of each village
    for (const Village &village: villages) {
        std::cout << "Village " << (village.isPlayer ? "belonging to the player" : "belonging to an AI")
                  << " is located at (" << village.x << ", " << village.y << ")." << std::endl;
    }
    std::cout << "\n=======================================================================\n" << std::endl;

    //------------------------------------------------------------------------------------------------------------------

    // Generate a map with all cells set to 0
    Map map = generateMap(MAP_WIDTH, MAP_HEIGHT);

    // Generate the AI and player villages
    std::vector<Village> newVillages = generateVillages(numPlayers, numAIs);

    // Output the map with the village locations
    printMap(map, villages);

    // Output information about each village
    for (const Village &village: newVillages) {
        std::cout << "\n" << std::endl;
        std::cout << "Village: ";
        if (village.isPlayer) {
            std::cout << "Player's village" << std::endl;
        } else {
            std::cout << "AI's village" << std::endl;
        }
        std::cout << "  Health: " << village.health << std::endl;
        std::cout << "  Resources: " << std::endl;
        std::cout << "    Wood: " << village.resources.wood << std::endl;
        std::cout << "    Gold: " << village.resources.gold << std::endl;
        std::cout << "    Food: " << village.resources.food << std::endl;
        std::cout << "  Buildings:" << std::endl;
        for (const Building &building: village.buildings) {
            std::cout << "    " << building.name << " (Level " << building.level << ")" << std::endl;
        }
        std::cout << "  Troops:" << std::endl;
        for (const Troop &troop: village.troops) {
            std::cout << "    Type: " << troop.type << " Attack: " << troop.attack << " Defense: "
                      << troop.defense << " Health: " << troop.health << std::endl;
        }
    }

    bool gameOver = false; // Flag to determine when the game should end

    // Start the game loop
    while (!gameOver) {
        // Start a new round
        std::cout << "\n=======================================================================\n" << std::endl;
        std::cout << "\t\t\t    ROUND ENDED." << std::endl;
        std::cout << "\n\t\t\tSTARTING NEW ROUND..." << std::endl;
        std::cout << "\n=======================================================================\n" << std::endl;

        // Turn phase
        std::cout << "\t\t\t    TURN PHASE..." << std::endl;
        for (auto &village: villages) {
            if (village.health > 0) { // Only take a turn if the village is still standing
                if (village.isPlayer) {
                    // Player's turn
                    takePlayerTurn(village, villages);
                } else {
                    // AI's turn
                    takeAITurn(village);
                }
            }
        }

        // Generate resources for each village
        for (auto &village: villages) {
            generateResources(village);
        }

        // Check win condition
        gameOver = winGame(villages);

        // Check if the user wants to continue playing
        gameOver = !gameIsRunning();
    }

    // Update the game state

    // Render the game

    return 0;
}
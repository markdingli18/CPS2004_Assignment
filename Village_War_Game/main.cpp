#include <iostream>
#include <vector>

#define MAP_HEIGHT 50
#define MAP_WIDTH 50

////--------------------------------------------------------------------------------------------------------------------

//// Variables
int numPlayers;
int numAIs;

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
    int trainingTime; // Time it takes to train a troop (if applicable)
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
    Resources costToUpgrade;
};

struct Village {
    int x; // x coordinate of the village
    int y; // y coordinate of the village
    int health; // health of the village
    bool isPlayer; // flag to indicate whether the village belongs to the player or an AI
    std::vector<Building> buildings; // vector of buildings in the village
    std::vector<Troop> troops; // vector of troops in the village
    Resources resources;
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
    std::cout << "\n===================================================================================================\n" << std::endl;

}

//----------------------------------------------------------------------------------------------------------------------
//// Troops
// Initialize the Troop objects
void initTroops(Troop &swordTroop, Troop &archerTroop, Troop &cavalryTroop) {
    swordTroop.type = "Swordsman";
    swordTroop.attack = 10;
    swordTroop.defense = 5;
    swordTroop.health = 20;
    swordTroop.trainingCost = 15;
    swordTroop.carryingCapacity = 10;
    swordTroop.marchingSpeed = 3;
    swordTroop.costToUpgrade = {50, 30, 20};

    archerTroop.type = "Archer";
    archerTroop.attack = 8;
    archerTroop.defense = 3;
    archerTroop.health = 15;
    archerTroop.trainingCost = 12;
    archerTroop.carryingCapacity = 8;
    archerTroop.marchingSpeed = 4;
    archerTroop.costToUpgrade = {40, 20, 10};

    cavalryTroop.type = "Cavalry";
    cavalryTroop.attack = 12;
    cavalryTroop.defense = 8;
    cavalryTroop.health = 25;
    cavalryTroop.trainingCost = 20;
    cavalryTroop.carryingCapacity = 15;
    cavalryTroop.marchingSpeed = 5;
    cavalryTroop.costToUpgrade = {60, 40, 30};
}

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
            troop.trainingCost = 50;
            troop.carryingCapacity = 20;
            troop.marchingSpeed = 3;
            troop.costToUpgrade = {80, 30, 30};
        } else if (i == 1) {
            troop.type = "Archer";
            troop.attack = 5;
            troop.defense = 10;
            troop.health = 20;
            troop.trainingCost = 40;
            troop.carryingCapacity = 10;
            troop.marchingSpeed = 5;
            troop.costToUpgrade = {70, 40, 20};
        } else {
            troop.type = "Cavalry";
            troop.attack = 12;
            troop.defense = 7;
            troop.health = 35;
            troop.trainingCost = 60;
            troop.carryingCapacity = 15;
            troop.marchingSpeed = 4;
            troop.costToUpgrade = {100, 50, 50};
        }
        troops.push_back(troop);
    }

    return troops;
}

// Upgrade Troops with resources Function
bool upgradeTroop(Village &village, Troop &troop) {
    // Check if the village has enough resources to upgrade the troop
    if (village.resources.wood >= troop.costToUpgrade.wood &&
        village.resources.gold >= troop.costToUpgrade.gold &&
        village.resources.food >= troop.costToUpgrade.food) {
        // Deduct the upgrade cost from the village's resources
        village.resources.wood -= troop.costToUpgrade.wood;
        village.resources.gold -= troop.costToUpgrade.gold;
        village.resources.food -= troop.costToUpgrade.food;
        // Increase the troop's attack, defense, and health
        troop.attack += 2;
        troop.defense += 2;
        troop.health += 5;
        // Increase the cost to upgrade the troop
        troop.costToUpgrade.wood += 10;
        troop.costToUpgrade.gold += 5;
        troop.costToUpgrade.food += 3;
        return true;
    }
    return false;
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
            building.resourceGenerationRate = 10;
            building.costToUpgrade = {100, 50, 30};
        } else if (i == 1) {
            building.name = "Lumber Mill";
            building.resourceGenerationRate = 5;
            building.costToUpgrade = {80, 40, 20};
        } else {
            building.name = "Farm";
            building.resourceGenerationRate = 3;
            building.costToUpgrade = {60, 30, 10};
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
            building.trainingTime = 5;
            building.costToUpgrade = {200, 100, 60};
        } else if (i == 1) {
            building.name = "Archery Range";
            building.troopGenerationCost = 40;
            building.trainingTime = 3;
            building.costToUpgrade = {160, 80, 40};
        } else {
            building.name = "Stables";
            building.troopGenerationCost = 60;
            building.trainingTime = 7;
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
            building.resourceGenerationRate += 5;
        } else {
            building.troopGenerationCost += 20;
            building.trainingTime -= 1;
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
//// Villages
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
        villages.push_back(aiVillage);
    }

    return villages;
}

////--------------------------------------------------------------------------------------------------------------------

////Functions
// Return true if the user wants to continue playing, false otherwise
bool gameIsRunning() {
    // Prompt the user to continue or quit
    std::cout << "=======================================================================\n" << std::endl;
    std::cout << "Enter Q to quit or any other key to continue: ";
    char input;
    std::cin >> input;
    if (input == 'Q' || input == 'q') {
        std::cout << "\n=======================================================================\n" << std::endl;
        std::cout << "\t\t\tQUITTING THE GAME...\n";
        std::cout << "\n=======================================================================\n" << std::endl;
        return false;
    }
    return true;
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
    for (const Village &village : newVillages) {
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
        for (const Building &building : village.buildings) {
            std::cout << "    " << building.name << " (Level " << building.level << ")" << std::endl;
        }
        std::cout << "  Troops:" << std::endl;
        for (const Troop &troop : village.troops) {
            std::cout << "    Type: " << troop.type << " Attack: " << troop.attack << " Defense: " << troop.defense << " Health: " << troop.health << std::endl;
        }
        std::cout << "\n=======================================================================\n" << std::endl;
    }

    // Start the game loop
    while (gameIsRunning()) {
        // Start a new round
        std::cout << "\n=======================================================================\n" << std::endl;
        std::cout << "\t\t\tSTARTING NEW ROUND..." << std::endl;
        std::cout << "\n=======================================================================\n" << std::endl;

        // Turn phase
        std::cout << "\t\t\t    TURN PHASE..." << std::endl;
        std::cout << "\n=======================================================================\n" << std::endl;
        for (auto& village : villages) {
            if (village.health > 0) {  // Only take a turn if the village is still standing
                if (village.isPlayer) {
                    // Player's turn

                } else {
                    // AI's turn

                }
            }
        }

        // Check if the win condition has been met
        bool gameWon = false;
        // the win condition when only the player's village is still standing
        for (auto& village : villages) {
            if (village.isPlayer && village.health > 0) {
                gameWon = true;
                break;
            }
            if (!village.isPlayer && village.health > 0) {
                gameWon = false;
                break;
            }
        }

        if (gameWon) {
            std::cout << "CONGRATULATIONS, YOU HAVE WON THE GAME!" << std::endl;
            break;
        }

        // Other round phases can be added here, such as resource generation or combat

        // Update the game state

        // Render the game
    }

    return 0;

}
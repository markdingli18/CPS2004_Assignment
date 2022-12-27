#ifndef MAIN_CPP_DO_ACTIONS_H
#define MAIN_CPP_DO_ACTIONS_H

#include "header.h"
#include "attack.h"

// Declare variables to keep track of the number of AI troops of each type
short AI_swordsmanCount = 0;
short AI_archerCount = 0;
short AI_cavalryCount = 0;

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

    // Check if the player has any troops to attack with
    bool hasTroops = false;
    if (swordsmanCount > 0 || archerCount > 0 || cavalryCount > 0) {
        hasTroops = true;
    }

    // If the player doesn't have any troops, and they try to choose action 3, ask them to choose a different action
    if (action == 3 && !hasTroops) {
        std::cout << "You don't have any troops to attack with. Please choose a different action.\n" << std::endl;
        doPlayerActions(village, villages);  // Recursive call to prompt player for a new action
        return;
    }

    // Perform the selected action
    if (action == 1) {
        // Loop until a valid building is chosen or the action is cancelled
        while (true) {
            // Display all the buildings in the village
            std::cout << "Buildings: " << std::endl;
            int i = 1;
            // Iterate through all the buildings in the village
            for (auto &building: village.buildings) {
                // Print the building's name and level
                std::cout << i << ". " << building.name << " (level " << building.level << ")" << std::endl;
                // Display the cost to upgrade the building
                std::cout << "Cost to upgrade: " << building.costToUpgrade.wood << " Wood, "
                          << building.costToUpgrade.gold << " Gold, " << building.costToUpgrade.food << " Food\n"
                          << std::endl;
                i++;
            }
            // Prompt the user to choose a building to upgrade
            std::cout << "Enter the number of the building you want to upgrade (or 0 to cancel): ";
            int buildingIndex;
            std::cin >> buildingIndex;
            // If the user chooses to cancel the action
            if (buildingIndex == 0) {
                // Cancel the action
                doPlayerActions(village, villages);
            }
                // If the user chooses a valid building
            else if (buildingIndex > 0 && buildingIndex <= village.buildings.size()) {
                // Get a reference to the chosen building
                Building &building = village.buildings[buildingIndex - 1];
                // Try to upgrade the building
                if (upgradeBuilding(village, building)) {
                    std::cout << "\n=======================================================================\n"
                              << std::endl;
                    // Print a success message
                    std::cout << "\t\t " << building.name << " upgraded to level " << building.level << "!"
                              << std::endl;
                    std::cout << "\n\tREMAINING RESOURCES: wood = " << village.resources.wood << ", gold - "
                              << village.resources.gold
                              << ", food - " << village.resources.food << std::endl;
                    // Exit the loop
                    break;
                }
                    // If the building cannot be upgraded
                else {
                    std::cout << "\n=======================================================================\n"
                              << std::endl;
                    // Print an error message
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
                int cost = troop.trainingCost;  // Initialize cost to the base training cost of the troop
                for (auto &building: village.buildings) {
                    // Check if the building is a training building
                    if (building.name == "Barracks" || building.name == "Archery Range" || building.name == "Stables") {
                        // Modify the cost of training the troop based on the level of the building
                        cost *= building.level;
                    }
                }
                std::cout << i << ". " << troop.type << " (" << cost << " from all Resources)" << std::endl;
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

                    std::cout << "\n=======================================================================\n"
                              << std::endl;
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

        // Wrap the checks in a loop
        while (true) {
            // Make sure the index is valid
            if (villageIndex < 0 || villageIndex >= villages.size() || villageIndex == 0) {
                std::cout << "Error: Invalid village index" << std::endl;
            }
                // If the index is valid
            else {
                Village &defendingVillage = villages[villageIndex];

                // Make sure the attacking village has at least one troop
                if (village.troops.empty()) {
                    std::cout << "Error: You don't have any troops to attack with" << std::endl;
                }
                    // Make sure the defending village is not the player's own village
                else if (defendingVillage.isPlayer) {
                    std::cout << "Error: You can't attack your own village" << std::endl;
                }
                    // If both the attacking village has troops and the defending village is not the player's own village
                else {
                    // Call the attackVillage function
                    attackVillage(village, defendingVillage);
                    // Exit the loop
                    break;
                }
            }

            // If the code reaches here, it means there was an error.
            // Ask the player to choose another village to attack
            std::cout << "\nEnter the index of the village you want to attack: ";
            std::cin >> villageIndex;
        }
    } else if (action == 4) {
        // Surrender action

        // Set the village's health to 0
        village.health = 0;

        // Print a message indicating that the village has been destroyed
        std::cout << "\n=======================================================================\n" << std::endl;
        std::cout << "\tYOU HAVE SURRENDERED! YOUR VILLAGE HAS BEEN DESTROYED!" << std::endl;
        std::cout << "\n=======================================================================\n" << std::endl;

        // Exit the game
        exit(0);
    } else if (action == 5) {
        // Pass turn action

        // Print a message indicating that the player has passed the turn
        std::cout << "\n=======================================================================\n" << std::endl;
        std::cout << "\t\t   Player has passed the turn." << std::endl;
        std::cout << "\n=======================================================================\n" << std::endl;
    } else {
        // Invalid action

        // Print a message indicating that the action is invalid
        std::cout << "\n=======================================================================\n" << std::endl;
        std::cout << "\t\t  Invalid action. Please try again." << std::endl;
        std::cout << "\n=======================================================================\n" << std::endl;

        // Prompt the player to enter a valid action
        doPlayerActions(village, villages);
    }
}

//------------------------------------------------------------------------------------------------------------------

void doAIActions(Village& village) {
    // Seed the random number generator with the current time
    std::srand(std::time(nullptr));

    bool actionSuccessful = false;
    while (!actionSuccessful) {
        // Create a random device object
        std::random_device rd;

        // Create a Mersenne Twister PRNG (pseudo-random number generator) using the random device as a seed
        std::mt19937 gen(rd());

        // Create a uniform integer distribution object with a range of 1 to 4
        std::uniform_int_distribution<> dis(1, 4);

        // Generate a random number within the specified range
        int AI_action = dis(gen);

        std::cout << "\n=======================================================================" << std::endl;
        std::cout << "\n\t\t\tAI chose action: " << AI_action << std::endl;

        // Check if the AI has any troops to attack with
        bool hasTroops = false;
        if (AI_swordsmanCount > 0 || AI_archerCount > 0 || AI_cavalryCount > 0) {
            hasTroops = true;
        }

        // If the player doesn't have any troops, and they try to choose action 3, ask them to choose a different action
        if (AI_action == 3 && !hasTroops) {
            doAIActions(village);
            return;
        }

        // Perform the selected action
        if (AI_action == 1) {
            // Upgrade buildings

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
            // Code for training troops

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
                        // Train the troops
                        village.resources.wood -= troop.trainingCost;
                        village.resources.gold -= troop.trainingCost;
                        village.resources.food -= troop.trainingCost;

                        // Determine how many troops to generate based on building levels
                        int AInumTroopsToGenerate = 1;  // default to 1 troop
                        for (auto &building: village.buildings) {
                            if (building.name == "Barracks" && troop.type == "Swordsman") {
                                AInumTroopsToGenerate = building.level;  // use the level of the Barracks building to determine how many troops to generate
                                break;  // no need to check other buildings, we found the right one
                            } else if (building.name == "Archery Range" && troop.type == "Archer") {
                                AInumTroopsToGenerate = building.level;  // use the level of the Archery Range building to determine how many troops to generate
                                break;  // no need to check other buildings, we found the right one
                            } else if (building.name == "Stables" && troop.type == "Cavalry") {
                                AInumTroopsToGenerate = building.level;  // use the level of the Stables building to determine how many troops to generate
                                break;  // no need to check other buildings, we found the right one
                            }
                        }

                        std::cout << "\n======================================================================="<< std::endl;

                        // print that the AI has trained a new troop
                        std::cout << "\n\t\t\tAI trained " << troop.type << "!" << std::endl;

                        // Set enoughResources to true to exit the loop
                        enoughResources = true;

                        // Increment the count of the corresponding troop type
                        if (troop.type == "Swordsman") {
                            AI_swordsmanCount++;
                        } else if (troop.type == "Archer") {
                            AI_archerCount++;
                        } else if (troop.type == "Cavalry") {
                            AI_cavalryCount++;
                        }

                        // Set actionSuccessful to true to indicate that the training was successful
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

                            // create a reference to newTroop in the village's troops vector
                            Troop &newTroop = village.troops[newTroopIndex];
                            if (village.resources.wood >= newTroop.trainingCost &&
                                village.resources.gold >= newTroop.trainingCost
                                && village.resources.food >= newTroop.trainingCost) {
                                // Check if there are enough resources to train the new troop
                                // subtract the training cost from the village's resources
                                village.resources.wood -= newTroop.trainingCost;
                                village.resources.gold -= newTroop.trainingCost;
                                village.resources.food -= newTroop.trainingCost;
                                std::cout << "\n=======================================================================\n"<< std::endl;
                                // print that the new troop has been trained
                                std::cout << "\n\t\tAI trained " << newTroop.type << "!" << std::endl;
                                // set enoughResources to true to exit the loop
                                enoughResources = true;
                                // set actionSuccessful to true to indicate that the training was successful
                                actionSuccessful = true;
                                // increment the count of the corresponding troop type
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
            //Attack village

            // call the aiAttackVillage function with the village as both arguments
            aiAttackVillage(village, village);
            // set actionSuccessful to true to indicate that the attack was successful
            actionSuccessful = true;
            break; // exit the loop

        } else if (AI_action == 4) {
            // Check if the AI has enough resources to perform any of the other actions
            bool actionSuccessful = false;

            // if the village has any buildings
            if (!village.buildings.empty()) {
                // select a random building
                int buildingIndex = std::rand() % village.buildings.size();
                // create a reference to the selected building
                Building &building = village.buildings[buildingIndex];
                // try to upgrade the building
                if (upgradeBuilding(village, building)) {
                    actionSuccessful = true; // set actionSuccessful to true if the upgrade was successful
                }
            }
            // if no action has been successful yet and the village has any troops
            if (!actionSuccessful && !village.troops.empty()) {
                // select a random troop
                int troopIndex = std::rand() % village.troops.size();
                // create a reference to the selected troop
                Troop &troop = village.troops[troopIndex];
                // check if the village has enough resources to train the troop
                if (village.resources.wood >= troop.trainingCost &&
                    village.resources.gold >= troop.trainingCost
                    && village.resources.food >= troop.trainingCost) {
                    // set actionSuccessful to true if the training can be performed
                    actionSuccessful = true;
                }
            }

            // If the AI doesn't have enough resources to perform any of the other actions, pass the turn
            if (!actionSuccessful) {
                // Code for passing the turn goes here
                std::cout << "\n=======================================================================" << std::endl;
                std::cout << "\n\t\t    AI passed the turn." << std::endl; // print that the AI has passed the turn
                std::cout << "\n=======================================================================\n" << std::endl;
            }
        }
    }
}

#endif //MAIN_CPP_DO_ACTIONS_H
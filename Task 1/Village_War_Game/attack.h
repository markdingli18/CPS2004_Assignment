#ifndef MAIN_CPP_ATTACK_H
#define MAIN_CPP_ATTACK_H

#include "header.h"

// variable declarations for number of each type of troop
short swordsmanCount = 0;
short archerCount = 0;
short cavalryCount = 0;

// function to attack a village
void attackVillage(Village &attackingVillage, Village &defendingVillage) {
    // Create a vector to store the selected troops
    std::vector<Troop> selectedTroops;

    // print information about the available troops
    std::cout << "\n=======================================================================\n"<< std::endl;
    std::cout << "Number of Swordsmen: " << swordsmanCount << std::endl;
    std::cout << "Number of Archers: " << archerCount << std::endl;
    std::cout << "Number of Cavalry: " << cavalryCount << std::endl;
    std::cout << "\n"<< std::endl;

    // Prompt the player to select swordsmen
    std::cout << "Enter the number of Swordsmen you want to send: ";
    int numSwordsmen;
    // loop to get input from the player
    while (true) {
        // check if the input is valid
        if (std::cin >> numSwordsmen) {
            // check if the number of troops selected is within the available range
            if (numSwordsmen >= 0 && numSwordsmen <= swordsmanCount) {
                break;  // exit loop if input is valid
            } else {
                std::cout << "Invalid input. Please enter a number between 0 and " << swordsmanCount << ": ";
            }
        } else {
            // clear the input stream and ignore any invalid characters
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number between 0 and " << swordsmanCount << ": ";
        }
    }

    // loop to select the specified number of Swordsmen troops
    for (int i = 0; i < numSwordsmen; i++) {
        // Find a Swordsmen troop to send
        bool foundTroop = false;
        // search through the attacking village's troops to find a Swordsmen
        for (size_t j = 0; j < attackingVillage.troops.size(); j++) {
            if (attackingVillage.troops[j].type == "Swordsman") {
                // add the troop to the selected troops vector and remove it from the attacking village's troops
                selectedTroops.push_back(attackingVillage.troops[j]);
                attackingVillage.troops.erase(attackingVillage.troops.begin() + j);
                foundTroop = true;
                break;  // exit inner loop once a Swordsmen is found
            }
        }
        // if no Swordsmen is found, print a message and exit the loop
        if (!foundTroop) {
            break;
        }
    }

    // Prompt the player to select Archers
    std::cout << "Enter the number of Archers you want to send: ";
    int numArchers;
    // loop to get input from the player
    while (true) {
    // check if the input is valid
        if (std::cin >> numArchers) {
            // check if the number of troops selected is within the available range
            if (numArchers >= 0 && numArchers <= archerCount) {
                break; // exit loop if input is valid
            } else {
                std::cout << "Invalid input. Please enter a number between 0 and " << archerCount << ": ";
            }
        } else {
            // clear the input stream and ignore any invalid characters
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number between 0 and " << archerCount << ": ";
        }
    }
    // loop to select the specified number of Archer troops
    for (int i = 0; i < numArchers; i++) {
        // Find an Archer troop to send
        bool foundTroop = false;
        // search through the attacking village's troops to find an Archer
        for (size_t j = 0; j < attackingVillage.troops.size(); j++) {
            if (attackingVillage.troops[j].type == "Archer") {
                // add the troop to the selected troops vector and remove it from the attacking village's troops
                selectedTroops.push_back(attackingVillage.troops[j]);
                attackingVillage.troops.erase(attackingVillage.troops.begin() + j);
                foundTroop = true;
                break; // exit inner loop once an Archer is found
            }
        }
        // if no Archer is found, print a message and exit the loop
        if (!foundTroop) {
            break;
        }
    }

    // Prompt the player to select cavalry
    std::cout << "Enter the number of Cavalry you want to send: ";
    int numCavalry;
    // loop to get input from the player
    while (true) {
        // check if the input is valid
        if (std::cin >> numCavalry) {
            // check if the number of troops selected is within the available range
            if (numCavalry >= 0 && numCavalry <= cavalryCount) {
                break; // exit loop if input is valid
            } else {
                std::cout << "Invalid input. Please enter a number between 0 and " << cavalryCount << ": ";
            }
        } else {
            // clear the input stream and ignore any invalid characters
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number between 0 and " << cavalryCount << ": ";
        }
    }
    // loop to select the specified number of Cavalry troops
    for (int i = 0; i < numCavalry; i++) {
        // Find a Cavalry troop to send
        bool foundTroop = false;
        // search through the attacking village's troops to find a Cavalry
        for (size_t j = 0; j < attackingVillage.troops.size(); j++) {
            if (attackingVillage.troops[j].type == "Cavalry") {
                // add the troop to the selected troops vector and remove it from the attacking village's troops
                selectedTroops.push_back(attackingVillage.troops[j]);
                attackingVillage.troops.erase(attackingVillage.troops.begin() + j);
                foundTroop = true;
                break; // exit inner loop once a Cavalry is found
            }
        }
        // if no Cavalry is found, print a message and exit the loop
        if (!foundTroop) {
            break;
        }
    }

    // Sum the attack of the selected troops
    int attackingVillageAttack = 0;
    for (const Troop &troop: selectedTroops) {
        // add the attack of each selected troop to the total attack of the attacking village
        attackingVillageAttack += troop.attack;
    }

    // Sum the attack of the troops in the defending army
    int defendingVillageAttack = 0;
    for (const Troop &troop: defendingVillage.troops) {
        // add the attack of each troop in the defending village to the total attack of the defending village
        defendingVillageAttack += troop.attack;
    }

    // Kill troops from both armies until the total health of the killed troops is equal to the opposing army's attack
    while (attackingVillageAttack > 0 && defendingVillageAttack > 0) {
        // Choose a random troop from the attacking village to kill
        int troopIndex = std::rand() % selectedTroops.size();
        Troop &troop = selectedTroops[troopIndex];
        // subtract the health of the chosen troop from the attacking village's attack
        attackingVillageAttack -= troop.health;
        // remove the chosen troop from the attacking village's troops
        selectedTroops.erase(selectedTroops.begin() + troopIndex);

        // Choose a random troop from the defending village to kill
        troopIndex = std::rand() % defendingVillage.troops.size();
        troop = defendingVillage.troops[troopIndex];
        // subtract the health of the chosen troop from the defending village's attack
        defendingVillageAttack -= troop.health;
        // remove the chosen troop from the defending village's troops
        defendingVillage.troops.erase(defendingVillage.troops.begin() + troopIndex);
    }

    // Check if the attack was successful
    if (!selectedTroops.empty()) {
        // Calculate the total attack of the surviving troops
        int totalAttack = 0;
        for (const Troop &troop: selectedTroops) {
            // add the attack of each surviving troop to the total attack
            totalAttack += troop.attack;
        }

        // Deal damage to the defending village
        // subtract the total attack from the defending village's health
        defendingVillage.health -= totalAttack;

        // Calculate the carrying capacity of the surviving troops
        int carryingCapacity = 0;
        for (const Troop &troop: selectedTroops) {
            // add the carrying capacity of each surviving troop to the total carrying capacity
            carryingCapacity += troop.carryingCapacity;
        }

        // Reduce resources from the defending village
        // subtract the carrying capacity from the defending village's food
        defendingVillage.resources.food -= carryingCapacity;
        // subtract the carrying capacity from the defending village's wood
        defendingVillage.resources.wood -= carryingCapacity;
        // subtract the carrying capacity from the defending village's gold
        defendingVillage.resources.gold -= carryingCapacity;

        // Output damage and resources lost from defending village
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

    // Seed a local random number generator with a random seed
    std::random_device rd;
    std::mt19937 rng(rd());

    // Generate a random number in the range [0, attacker.troops.size() - 1]
    std::uniform_int_distribution<int> dist(0, attacker.troops.size() - 1);

    // Generate random numbers for the number of troops the AI will use in the attack
    int swordsmen = dist(rng);
    int archers = dist(rng);
    int cavalry = dist(rng);

    // Make sure the AI is using at least one troop in the attack
    if (swordsmen == 0 && archers == 0 && cavalry == 0) {
        // Choose a random troop type to use in the attack
        std::uniform_int_distribution<int> dist(1, 3);
        int troopType = dist(rng);
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

    // Select the specified number of swordsmen
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

    // Select the specified number of archers
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

    // Select the specified number of cavalry
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
    while (!defender.troops.empty() && attackingVillageAttack >= defendingVillageAttack) {
        // Choose a random troop from the defending village to kill
        int index = std::rand() % defender.troops.size();
        Troop killedTroop = defender.troops[index];
        defendingVillageAttack -= killedTroop.health;
        defender.troops.erase(defender.troops.begin() + index);

        // Choose a random troop from the attacking village to kill
        index = std::rand() % selectedTroops.size();
        killedTroop = selectedTroops[index];
        attackingVillageAttack -= killedTroop.health;
        selectedTroops.erase(selectedTroops.begin() + index);
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
        // subtract the carrying capacity from the defending village's food
        defender.resources.food -= carryingCapacity;
        // subtract the carrying capacity from the defending village's wood
        defender.resources.wood -= carryingCapacity;
        // subtract the carrying capacity from the defending village's gold
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

#endif //MAIN_CPP_ATTACK_H
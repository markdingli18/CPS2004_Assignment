#ifndef MAIN_CPP_ATTACK_H
#define MAIN_CPP_ATTACK_H

#include "header.h"

short swordsmanCount = 0;
short archerCount = 0;
short cavalryCount = 0;

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

#endif //MAIN_CPP_ATTACK_H

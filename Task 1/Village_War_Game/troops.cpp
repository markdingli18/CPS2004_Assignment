#include "header.h"

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
        } else if (i == 1) {
            troop.type = "Archer";
            troop.attack = 5;
            troop.defense = 10;
            troop.health = 20;
            troop.trainingCost = 20;
            troop.carryingCapacity = 10;
        } else {
            troop.type = "Cavalry";
            troop.attack = 12;
            troop.defense = 7;
            troop.health = 35;
            troop.trainingCost = 40;
            troop.carryingCapacity = 25;
        }
        troops.push_back(troop);
    }

    return troops;
}
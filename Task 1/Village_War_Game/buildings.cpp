#include "header.h"

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

////--------------------------------------------------------------------------------------------------------------------

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
            building.costToUpgrade = {160, 80, 50};
        } else {
            building.name = "Stables";
            building.troopGenerationCost = 60;
            building.costToUpgrade = {220, 100, 60};
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
        // Update the resource generation rate and troop generation cost based on the new level
        if (building.type == "ResourceGenerator") {
            building.resourceGenerationRate += 10;
        } else {
            building.troopGenerationCost += 20;
        }
        // Increase the cost to upgrade the building
        building.costToUpgrade.wood += 100;
        building.costToUpgrade.gold += 90;
        building.costToUpgrade.food += 80;
        return true;
    }
    return false;
}
#include "header.h"

//// Resources
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
#include "header.h"

//// Map
// Generates Map
Map generateMap(int width, int height) { // Generates a Map object with a given width and height
    Map map;
    map.width = width; // Set the width of the map
    map.height = height; // Set the height of the map
    map.cells.resize(height); // Resize the cells vector to fit the given height
    for (int y = 0; y < height; y++) {
        map.cells[y].resize(width); // Resize the inner vector to fit the given width
        for (int x = 0; x < width; x++) {
// Set the value of each cell to 0
            map.cells[y][x] = 0;
        }
    }
    return map; // Return the generated map
}

////--------------------------------------------------------------------------------------------------------------------

// Prints the map to the console, along with the locations of the villages
void printMap(const Map& map, const std::vector<Village>& villages) {
    std::cout << "Game Map:\n" << std::endl;
    for (int y = 0; y < map.height; y++) {
        for (int x = 0; x < map.width; x++) {
            // Check if the current cell corresponds to the location of a village
            bool isVillage = false;
            for (const Village &village : villages) {
                if (village.x == x && village.y == y) {
                    // Check if the current cell is a village
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
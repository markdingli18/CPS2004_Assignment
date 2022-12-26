#include "header.h"

// Global Variables
short numPlayers;
short numAIs;

int main() {

    // Welcome Message
    welcome_message();

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

    // Output information about all villages
    villages_info(villages);

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

    return 0;
}
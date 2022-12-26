#include "header.h"

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
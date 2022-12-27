#include "header.h"
#include "do_actions.h"

void takePlayerTurn(Village &village, std::vector<Village> &villages) {
    // Player's turn
    std::cout << "\n=======================================================================\n"<< std::endl;
    std::cout << "\t\t\tPlayer's turn....\n" << std::endl;
    doPlayerActions(village, villages);
}

void takeAITurn(Village &village) {
    // AI's turn
    if (village.health > 0) {
        // only perform actions if the village is still standing
        std::cout << "\n=======================================================================\n"<< std::endl;
        std::cout << "\t\t\t   AI's turn...." << std::endl;
        doAIActions(village);
    }
}
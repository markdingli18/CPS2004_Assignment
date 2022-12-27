#include "header.h"

void welcome_message() {

// Help



// Display the top border
    std::cout << "=======================================================================\n" << std::endl;
    std::cout << "     /\\                                                        /\\\n"
                 "    |  |                                                      |  |\n"
                 "   /----\\                  Village War Game                  /----\\\n"
                 "  [______]                                                  [______]\n"
                 "   |    |         _____                        _____         |    |\n"
                 "   |[]  |        [     ]                      [     ]        |  []|\n"
                 "   |    |       [_______][ ][ ][ ][][ ][ ][ ][_______]       |    |\n"
                 "   |    [ ][ ][ ]|     |  ,----------------,  |     |[ ][ ][ ]    |\n"
                 "   |             |     |/'    ____..____    '\\|     |             |\n"
                 "    \\  []        |     |    /'    ||    '\\    |     |        []  /\n"
                 "     |      []   |     |   |o     ||     o|   |     |  []       |\n"
                 "     |           |  _  |   |     _||_     |   |  _  |           |\n"
                 "     |   []      | (_) |   |    (_||_)    |   | (_) |       []  |\n"
                 "     |           |     |   |     (||)     |   |     |           |\n"
                 "     |           |     |   |      ||      |   |     |           |\n"
                 "   /''           |     |   |o     ||     o|   |     |           ''\\\n"
                 "  [_____________[_______]--'------''------'--[_______]_____________]\n" << std::endl;
    std::cout << "=======================================================================\n" << std::endl;
    // Display the welcome message
    std::cout << " WELCOME TO THE VILLAGE WAR GAME! IN THIS GAME, YOU PLAY AS THE LEADER" << std::endl;
    std::cout << "  OF A VILLAGE, AND YOUR GOAL IS TO DESTROY ALL OF THE AI-CONTROLLED" << std::endl;
    std::cout << " VILLAGES WHILE PROTECTING YOUR OWN. YOU WILL TAKE TURNS AGAINST THE" << std::endl;
    std::cout << "   AIS, AND ON EACH TURN YOU CAN CHOOSE TO ATTACK ONE OF THE ENEMY" << std::endl;
    std::cout << "  VILLAGES OR UPGRADE YOUR OWN VILLAGE'S BUILDINGS. UPGRADING YOUR" << std::endl;
    std::cout << "   VILLAGE'S BUILDINGS WILL ALLOW YOU TO GENERATE MORE TROOPS AND" << std::endl;
    std::cout << "  RESOURCES, WHICH WILL HELP YOU IN YOUR ATTACKS AGAINST THE ENEMY" << std::endl;
    std::cout << " VILLAGES. THE HIGHER THE LEVEL OF YOUR BUILDINGS, THE MORE TROOPS" << std::endl;
    std::cout << "AND RESOURCES YOU WILL GENERATE EVERY ROUND! BE CAREFUL, AS THE AI" << std::endl;
    std::cout << "   WILL ALSO BE ATTACKING YOUR VILLAGE AND TRYING TO DESTROY IT." << std::endl;
    std::cout << "IF YOUR VILLAGE'S HEALTH REACHES 0, YOU LOSE THE GAME. IF YOU MANAGE" << std::endl;
    std::cout << " \t  TO DESTROY ALL OF THE AI VILLAGES, YOU WIN! " << std::endl;
    std::cout << " \n\t\t\t   GOOD LUCK!\n" << std::endl;

    // Display the bottom border
    std::cout << "=======================================================================\n" << std::endl;
}
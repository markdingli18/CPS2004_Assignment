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
    std::cout << "\t\t WELCOME TO VILLAGE WAR!" << std::endl;
    std::cout << "ASSEMBLE YOUR TROOPS AND DEFEND YOUR VILLAGE FROM INVADING FORCES!" << std::endl;
    std::cout << "\t\tMAY THE GODS BE WITH YOU IN BATTLE.\n" << std::endl;
// Display the bottom border
    std::cout << "=======================================================================\n" << std::endl;
}
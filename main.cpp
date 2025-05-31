#include "Game.h"
#include <iostream>

int main()
{
    // --- Mode selection ---
    std::cout << "Select Battle Mode:\n"
              << "1) The Swiftstrike (5x8)\n"
              << "2) The Starlight Clash (8x10)\n"
              << "3) Wrath of Titans (10x12)\n"
              << "Choice: ";
    int choice = 1;
    std::cin >> choice;

    BattleMode mode;
    int rows, cols;
    switch (choice)
    {
        case 2:  mode = STARLIGHT_CLASH;  rows = 8;  cols = 10; break;
        case 3:  mode = WRATH_OF_TITANS;  rows = 10; cols = 12; break;
        default: mode = SWIFTSTRIKE;      rows = 5;  cols = 8;  break;
    }

    // --- Commander names ---
    char name1[50];
    char name2[50];
    std::cout << "Enter Rebel commander name: ";
    std::cin  >> name1;
    std::cout << "Enter Imperial commander name: ";
    std::cin  >> name2;

    // Start the game
    Game game(mode, name1, name2, rows, cols);
    game.start();

    return 0;
}

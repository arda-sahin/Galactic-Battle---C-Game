#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

int main()
{
    //Mode selection
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

    // Commander names
    char plyr1[50];
    char plyr2[50];
    std::cout << "Enter Rebel commander name: ";
    std::cin >> plyr1;
    std::cout << "Enter Imperial commander name: ";
    std::cin >> plyr2;

    // Randomly choose who starts
    std::srand((int)std::time(0));
    int first = std::rand() % 2; // 0: Rebel starts, 1:Imperial starts

    if (first == 1)
    {
        // swap names so that player[1] can start first (instead Player[0])
        char temp[50];
        std::strcpy(temp, plyr1);
        std::strcpy(plyr1, plyr2);
        std::strcpy(plyr2, temp);
    }

    std::cout << "\n>> " << plyr1 << " will start the game!\n";

    // Start the game
    Game game(mode, plyr1, plyr2, rows, cols);
    game.start();

    return 0;
}

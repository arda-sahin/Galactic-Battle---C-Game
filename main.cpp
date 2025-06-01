#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

int main()
{
    //Mode selection
    cout << "Select Battle Mode:\n"
              << "1) The Swiftstrike\n"
              << "2) The Starlight Clash\n"
              << "3) Wrath of Titans\n"
              << "Choice: ";
    int choice;
    cin >> choice;

    BattleMode mode;
    int rows, cols;

    if (choice == 2) {
        mode = STARLIGHT_CLASH;
        rows = 8;
        cols = 10;
    }
    else if (choice == 3) {
        mode = WRATH_OF_TITANS;
        rows = 10;
        cols = 12;
    }
    else {
        mode = SWIFTSTRIKE;
        rows = 5;
        cols = 8;
    }


    // Commander names
    char plyr1[50];
    char plyr2[50];
    cout << "Enter Rebel commander name: "; cin >> plyr1;
    cout << "Enter Imperial commander name: "; cin >> plyr2;

    // Randomly choose who starts
    srand((int)time(0));
    int first = rand() % 2; // 0: Rebel starts, 1:Imperial starts

    if (first == 1) {
        // swap names so that player[1] can start first (instead Player[0])
        char temp[50];
        strcpy(temp, plyr1);
        strcpy(plyr1, plyr2);
        strcpy(plyr2, temp);
    }

    cout << "\n>> " << plyr1 << " will start the game!\n";

    // Start the game
    Game game(mode, plyr1, plyr2, rows, cols);
    game.start();

    return 0;
}

#include "Game.h"
#include "StarDestroyer.h"
#include "MonCalamariCruiser.h"
#include "XWingSquadron.h"
#include "TIEFighter.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

// -------------- Constructor / Destructor --------------
Game::Game()
        : mode(SWIFTSTRIKE),
          currentPlayer(0),
          rows(5),
          cols(8)
{
    players[0] = nullptr;
    players[1] = nullptr;

    std::srand((int)std::time(0));   // Seed RNG
}

Game::~Game()
{
    delete players[0];
    delete players[1];
}

// -------------- Private Helpers --------------
void Game::setupMode()
{
    std::cout << "Select Battle Mode:\n"
              << "1) The Swiftstrike (5x8)\n"
              << "2) The Starlight Clash (8x10)\n"
              << "3) Wrath of Titans (10x12)\n"
              << "Choice: ";

    int choice = 1;
    std::cin >> choice;

    switch (choice)
    {
        case 2:
            mode = STARLIGHT_CLASH; rows = 8;  cols = 10; break;
        case 3:
            mode = WRATH_OF_TITANS; rows = 10; cols = 12; break;
        default:
            mode = SWIFTSTRIKE;     rows = 5;  cols = 8;  break;
    }
}

void Game::setupPlayers()
{
    char name1[50];
    char name2[50];

    std::cout << "Enter Rebel commander name: ";
    std::cin >> name1;
    std::cout << "Enter Imperial commander name: ";
    std::cin >> name2;

    players[0] = new Player(name1, rows, cols);
    players[1] = new Player(name2, rows, cols);

    // Fleet composition per mode
    int sd, mc, xw, tie;
    if (mode == SWIFTSTRIKE)           { sd = 1; mc = 1; xw = 1; tie = 2; }
    else if (mode == STARLIGHT_CLASH)  { sd = 2; mc = 2; xw = 2; tie = 4; }
    else                               { sd = 4; mc = 3; xw = 3; tie = 4; }

    // Add ships to both players
    for (int p = 0; p < 2; ++p)
    {
        int id = 0;
        for (int i = 0; i < sd;  ++i) players[p]->addShip(new StarDestroyer(++id));
        for (int i = 0; i < mc;  ++i) players[p]->addShip(new MonCalamariCruiser(++id));
        for (int i = 0; i < xw;  ++i) players[p]->addShip(new XWingSquadron(++id));
        for (int i = 0; i < tie; ++i) players[p]->addShip(new TIEFighter(++id));
    }
}

void Game::placementPhase()
{
    players[0]->deployFleet();
    players[1]->deployFleet();
}

void Game::battlePhase()
{
    while (!checkVictory())
    {
        Player* attacker = players[currentPlayer];
        Player* defender = players[1 - currentPlayer];

        attacker->printBoards(false);
        attacker->takeTurn(*defender);

        // TODO: applyDiceEffect(attacker);

        attacker->printStats();
        defender->printStats();

        if (!checkVictory())
        {
            switchTurn();
        }
    }

    std::cout << "\n*** Victory! Commander "
              << players[currentPlayer]->getName()
              << " wins the battle! ***\n";
}

void Game::applyDiceEffect(Player& /*player*/)
{
    // TODO: implement random bonus / penalty after 2+ hits
}

bool Game::checkVictory() const
{
    return players[0]->remainingShips() == 0 ||
           players[1]->remainingShips() == 0;
}

void Game::switchTurn()
{
    currentPlayer = 1 - currentPlayer;
}

// -------------- Public --------------
void Game::start()
{
    setupMode();
    setupPlayers();
    placementPhase();
    battlePhase();
}

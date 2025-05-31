#include "Game.h"
#include "StarDestroyer.h"
#include "MonCalamariCruiser.h"
#include "XWingSquadron.h"
#include "TIEFighter.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

// Constructor / Destructor
Game::Game(BattleMode m,
           const char* name1,
           const char* name2,
           int r,
           int c)
        : mode(m),
          currentPlayer(0),
          rows(r),
          cols(c)
{
    // Create players
    players[0] = new Player(name1, rows, cols);
    players[1] = new Player(name2, rows, cols);

    // Fleet composition based on chosen mode
    int sd, mc, xw, tie;
    if (mode == SWIFTSTRIKE)          { sd = 1; mc = 1; xw = 1; tie = 2; }
    else if (mode == STARLIGHT_CLASH) { sd = 2; mc = 2; xw = 2; tie = 4; }
    else                              { sd = 4; mc = 3; xw = 3; tie = 4; }

    // Add ships to both players
    for (int p = 0; p < 2; ++p)
    {
        int id = 0;
        for (int i = 0; i < sd;  ++i) players[p]->addShip(new StarDestroyer(++id));
        for (int i = 0; i < mc;  ++i) players[p]->addShip(new MonCalamariCruiser(++id));
        for (int i = 0; i < xw;  ++i) players[p]->addShip(new XWingSquadron(++id));
        for (int i = 0; i < tie; ++i) players[p]->addShip(new TIEFighter(++id));
    }

    std::srand((int)std::time(0));   // Seed RNG once
}

Game::~Game()
{
    delete players[0];
    delete players[1];
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
        int hitsThisTurn = attacker->takeTurn(*defender);

        applyDiceEffect(*attacker, hitsThisTurn);

        attacker->printStats();
        defender->printStats();

        if (!checkVictory())
            switchTurn();
    }

    std::cout << "\n*** Victory! Commander "
              << players[currentPlayer]->getName()
              << " wins the battle! ***\n";
}


// Dice mechanic: if ≥2 hits → 1/6 chance to skip next turn
void Game::applyDiceEffect(Player& attacker, int hitsThisTurn)
{
    if (hitsThisTurn < 2) return;

    int roll = (std::rand() % 6) + 1;
    std::cout << "  > Dice rolled: " << roll << "\n";
    if (roll == 1)
    {
        std::cout << "  > Penalty: weapons overheated, next turn skipped.\n";
        attacker.setSkip(true);
    }
    else
    {
        std::cout << "  > No special effect.\n";
    }
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

void Game::start()
{
    placementPhase();
    battlePhase();
}

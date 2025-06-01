#include "Game.h"
#include "StarDestroyer.h"
#include "MonCalamariCruiser.h"
#include "XWingSquadron.h"
#include "TIEFighter.h"
#include "GiftSystem.h"
#include <iostream>

using namespace std;

// Constructor / Destructor
Game::Game(BattleMode m, const char* p1, const char* p2, int r, int c)
{
    // Set game mode and initial values
    mode = m;
    currentPlayer = 0;
    rows = r; cols = c;

    // Create two players with given names and board size
    players[0] = new Player(p1, rows, cols);
    players[1] = new Player(p2, rows, cols);

    // Determine number of ships for each type based on mode
    int sd;
    int mc;
    int xw;
    int tie;
    if (mode == SWIFTSTRIKE) {
        sd = 1;
        mc = 1;
        xw = 1;
        tie = 2;
    }
    else if (mode == STARLIGHT_CLASH) {
        sd = 2;
        mc = 2;
        xw = 2;
        tie = 4;
    }
    else {
        sd = 4;
        mc = 3;
        xw = 3;
        tie = 4;
    }

    // Add ships to each player
    int p = 0;
    while (p < 2) {
        int id = 0;
        int i = 0;

        // Add Star Destroyers
        while (i < sd) {
            id = id + 1;
            StarDestroyer* ship = new StarDestroyer(id);
            players[p]->addShip(ship);
            i = i + 1;
        }

        // Add Mon Calamari Cruisers
        i = 0;
        while (i < mc) {
            id = id + 1;
            MonCalamariCruiser* ship = new MonCalamariCruiser(id);
            players[p]->addShip(ship);
            i = i + 1;
        }

        // Add X-Wing Squadrons
        i = 0;
        while (i < xw) {
            id = id + 1;
            XWingSquadron* ship = new XWingSquadron(id);
            players[p]->addShip(ship);
            i = i + 1;
        }

        // Add TIE Fighters
        i = 0;
        while (i < tie) {
            id = id + 1;
            TIEFighter* ship = new TIEFighter(id);
            players[p]->addShip(ship);
            i = i + 1;
        }

        p = p + 1;
    }
}

Game::~Game() {
    delete players[0];
    delete players[1];
}

void Game::placementPhase() {
    players[0]->deployFleet();
    players[1]->deployFleet();
}

void Game::battlePhase() {

    while (!checkVictory()) {

        Player* attacker = players[currentPlayer];
        Player* defender = players[1 - currentPlayer];

        // BEFORE SHOOTING: Display both boards
        cout << "\n--- " << attacker->getName() << "'s turn: CURRENT BOARDS ---\n";
        attacker->printBoards(false);

        int hitsThisTurn = attacker->takeTurn(*defender);

        //victory check
        if (checkVictory())
            break;

        // AFTER SHOOTING: Show updated boards
        cout << "\n--- " << attacker->getName() << "'s turn: UPDATED BOARDS ---\n";
        attacker->printBoards(false);

        attacker->printStats();
        defender->printStats();

        // Gift system
        bool extraTurn = GiftSystem::applyGift(attacker, defender, mode, hitsThisTurn);

        if (!checkVictory() && !extraTurn)
            switchTurn();
        else if (extraTurn)
            cout << "--Extra turn!\n";

    }

    cout << "\n*** Victory!" << players[currentPlayer]->getName() << " wins the battle! ***\n";
}

bool Game::checkVictory() const {
    return players[0]->remainingShips() == 0 || players[1]->remainingShips() == 0;
}

void Game::switchTurn() {
    currentPlayer = 1 - currentPlayer;
}

void Game::start() {
    placementPhase();
    battlePhase();
}

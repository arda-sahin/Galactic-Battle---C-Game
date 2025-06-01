#include "GiftSystem.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Game.h"

using namespace std;

// create ship
static BattleShip* createRandomShip(int roll, int id)
{
    if (roll <= 10) { //%10
        return new StarDestroyer(id);
    }
    else if (roll <= 30) { //%20
        return new MonCalamariCruiser(id);
    }
    else if (roll <= 60) { //%30
        return new XWingSquadron(id);
    }
    else { //%40
        return new TIEFighter(id);
    }
}

// to place ship randomly on board
static bool tryPlaceRandom(Player* player,BattleShip* ship)
{
    Board* board = player->getOwnBoard();
    int rows = board->getRows();
    int cols = board->getCols();

    int dR[8]={-1,-1,0,1,1,1,0,-1};
    int dC[8]={0,1,1,1,0,-1,-1,-1};

    for (int attempt=0; attempt<200; ++attempt)
    {
        int r = rand()%rows;
        int c = rand()%cols;
        Coordinate start(r,c);

        int dir = rand()%8;
        Coordinate end;
        end.row = r + dR[dir]*(ship->getSize()-1);
        end.col = c + dC[dir]*(ship->getSize()-1);

        if (board->placeShip(ship,start,end))
            return true;
    }
    return false;
}

bool GiftSystem::applyGift(Player* attacker, Player* defender, BattleMode mode, int hitsThisTurn) {
    if (hitsThisTurn < 2) return false;
    int g = (rand()%100)+1;  // 1-100

    //GIFT1: add ship
    if (g <= 10)
    {
        int roll = (rand()%100)+1;
        int newId = attacker->getFleetSize()+1;
        BattleShip* ship = createRandomShip(roll,newId);

        if (tryPlaceRandom(attacker,ship)) {
            attacker->addShip(ship);
            cout << ">> Gift: Extra ship added to your fleet!\n";
        }
        else {
            delete ship;
            cout << ">> Gift tried to add a ship but no space left.\n";
        }
        return false;
    }

    // GIFT2: shoot again
    if (g <= 40)  // 11-40 (30%)
    {
        cout << ">> Gift: You may shoot again now!\n";
        int extraHits = attacker->takeTurn(*defender);
        return false;
    }

    //GIFT3: enemy -1 shot next turn
    if (g <= 60)   // 41-60 (20%)
    {
        std::cout << ">> Gift: Opponent loses one shot next turn.\n";
        defender->setReduceOneNextTurn();
        return false;
    }

    // GIFT4 : enemy only 1 shot next turn
    if (g <= 80)   // 61-80 (20%)
    {
        cout << ">> Gift: Opponent limited to ONE shot next turn.\n";
        defender->setLimitOneNextTurn();
        return false;
    }

    //GIFT5: extra turn
    cout << ">> Gift: You gain an extra turn!\n";
    return true; // attacker plays again
}

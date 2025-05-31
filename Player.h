#ifndef PLAYER_H
#define PLAYER_H

#include "Board.h"
#include "BattleShip.h"

class Player
{
private:
    char       name[50];
    Board*     ownBoard;
    Board*     targetBoard;
    BattleShip* fleet[20];
    int        fleetSize;

    int totalShots;
    int hits;
    int misses;

    void countRemainingTypes(int& sd,int& mc, int& xw,int& tie) const;

public:
    Player(const char* playerName, int rows, int cols);
    ~Player();

    void addShip(BattleShip* ship);
    void deployFleet();
    int  takeTurn(Player& enemy); // returns hits this turn

    int  remainingShips() const;
    int  maxLaserBursts() const;


    const char* getName() const;
    void printStats() const;
    void printBoards(bool revealShips) const;

    Board* getOwnBoard()    const;
    Board* getTargetBoard() const;
};

#endif

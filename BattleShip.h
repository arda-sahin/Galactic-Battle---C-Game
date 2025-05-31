#ifndef A3_BATTLESHIP_H
#define A3_BATTLESHIP_H
#include "Coordinate.h"

class Board;

class BattleShip
{
protected:
    int         size;
    int         hitsToDestroy;
    int         laserBursts;
    bool        status; //status 1: sunk
    int         hitCount; // How many times the ship has been hit
    char        symbol;  // Grid symbol (size digit)

public:
    BattleShip(int sz, int hits, int bursts, char sym, int id);
    virtual ~BattleShip();

    virtual void shoot(Board& target) = 0;

    // Accessors
    bool isSunk()         const;
    int  getLaserBursts() const;
    char getSymbol()      const;
    int  getSize()        const;


    void registerHit();  //Called when the ship is hit
    Coordinate* cells;
};

#endif //A3_BATTLESHIP_H

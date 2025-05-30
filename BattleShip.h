#ifndef A3_BATTLESHIP_H
#define A3_BATTLESHIP_H

#include "Coordinate.h"

class Board;          // Forward declaration

class BattleShip
{
protected:
    int         size;            // Number of cells the ship occupies
    int         hitsToDestroy;   // Hits required to sink
    int         laserBursts;     // Shots per turn when operative
    // Dynamic array of ship coordinates
    bool        sunk;            // Status flag
    int         hitCount;        // How many times the ship has been hit
    int         shipId;          // Unique id inside its type
    char        symbol;          // Grid symbol (size digit)

public:
    BattleShip(int sz, int hits, int bursts, char sym, int id);
    virtual ~BattleShip();

    virtual void shoot(Board& target) = 0;   // Pure virtual - implemented in subclasses

    // Accessors
    bool isSunk()         const;
    int  getLaserBursts() const;
    char getSymbol()      const;
    int  getSize()        const;

    // Mutators
    void registerHit();   // Called when the ship is hit
    Coordinate* cells;
};

#endif //A3_BATTLESHIP_H

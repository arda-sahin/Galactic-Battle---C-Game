#ifndef A3_BOARD_H
#define A3_BOARD_H

#include "Coordinate.h"

class BattleShip;

class Board
{
private:
    int   rows;
    int   cols;
    char** grid;

public:
    Board(int r, int c);
    ~Board();

    bool placeShip(BattleShip* ship,
                   const Coordinate& start,
                   const Coordinate& end);

    bool isInside(const Coordinate& coord)  const;
    bool isOccupied(const Coordinate& coord) const;

    bool markHit(const Coordinate& coord);  // Returns true if a ship cell is hit
    char getCell(const Coordinate& coord) const;
    void setCell(const Coordinate& coord, char value);

    void display(bool revealShips) const; // Prints the board

    int  getRows() const;
    int  getCols() const;
};

#endif //A3_BOARD_H

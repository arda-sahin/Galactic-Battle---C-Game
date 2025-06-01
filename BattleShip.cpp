#include "BattleShip.h"

BattleShip::BattleShip(int sz, int hits, int bursts, char sym, int id)
        : size(sz),
          hitsToDestroy(hits),
          laserBursts(bursts),
          cells(nullptr),
          status(false),
          hitCount(0),
          symbol(sym)
{
    // Allocate array for ship coordinates
    cells = new Coordinate[size];
}

BattleShip::~BattleShip()
{
    delete[] cells;
}

bool BattleShip::isSunk() const
{
    return status;
}

int BattleShip::getLaserBursts() const
{
    return laserBursts;
}

char BattleShip::getSymbol() const
{
    return symbol;
}

int BattleShip::getSize() const
{
    return size;
}

void BattleShip::registerHit()
{
    hitCount = hitCount + 1;
    if (hitCount >= hitsToDestroy) {
        status = true; //sunk
    }
}

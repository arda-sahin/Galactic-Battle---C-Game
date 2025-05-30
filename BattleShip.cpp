#include "BattleShip.h"
#include <cstring>   // For memset (if needed)

BattleShip::BattleShip(int sz, int hits, int bursts, char sym, int id)
        : size(sz),
          hitsToDestroy(hits),
          laserBursts(bursts),
          cells(nullptr),
          sunk(false),
          hitCount(0),
          shipId(id),
          symbol(sym)
{
    // Allocate array for ship coordinates; will be filled during placement
    cells = new Coordinate[size];
}

BattleShip::~BattleShip()
{
    delete[] cells;
}

bool BattleShip::isSunk() const
{
    return sunk;
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
    ++hitCount;
    if (hitCount >= hitsToDestroy)
    {
        sunk = true;
    }
}

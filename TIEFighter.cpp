#include "TIEFighter.h"

// TIEFighter constructor: sets size=1, maxHits=1, laserBursts=1, symbol=1
TIEFighter::TIEFighter(int id)
        : BattleShip(1, 1, 1, '1', id)
{
}

void TIEFighter::shoot(Board& target)
{
}

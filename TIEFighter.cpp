#include "TIEFighter.h"

// TIE Fighter: size 1, hits 1, laser bursts 1, symbol '1'
TIEFighter::TIEFighter(int id)
        : BattleShip(1, 1, 1, '1', id)
{
}

void TIEFighter::shoot(Board& target)
{
    // TODO: Implement TIE Fighter firing behaviour
}

#ifndef A3_TIEFIGHTER_H
#define A3_TIEFIGHTER_H

#include "BattleShip.h"

class TIEFighter : public BattleShip
{
public:
    TIEFighter(int id);
    void shoot(Board& target) override;
};

#endif //A3_TIEFIGHTER_H

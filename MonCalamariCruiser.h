#ifndef A3_MONCALAMARICRUISER_H
#define A3_MONCALAMARICRUISER_H

#include "BattleShip.h"

class MonCalamariCruiser : public BattleShip
{
public:
    MonCalamariCruiser(int id);
    void shoot(Board& target) override;
};

#endif //A3_MONCALAMARICRUISER_H

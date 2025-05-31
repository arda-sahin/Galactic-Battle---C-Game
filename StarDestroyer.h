#ifndef A3_STARDESTROYER_H
#define A3_STARDESTROYER_H

#include "BattleShip.h"

class StarDestroyer : public BattleShip
{
public:
    StarDestroyer(int id);
    void shoot(Board& target) override;
};

#endif //A3_STARDESTROYER_H

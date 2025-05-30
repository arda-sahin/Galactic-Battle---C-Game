#ifndef A3_XWINGSQUADRON_H
#define A3_XWINGSQUADRON_H

#include "BattleShip.h"

class XWingSquadron : public BattleShip
{
public:
    XWingSquadron(int id);
    void shoot(Board& target) override;
};

#endif //A3_XWINGSQUADRON_H

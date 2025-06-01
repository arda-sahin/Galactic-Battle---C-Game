#ifndef A3_GIFTSYSTEM_H
#define A3_GIFTSYSTEM_H

#include "Player.h"
#include "StarDestroyer.h"
#include "MonCalamariCruiser.h"
#include "XWingSquadron.h"
#include "TIEFighter.h"
#include "Game.h"

class GiftSystem
{
public:
    static bool applyGift(Player* attacker,
                          Player* defender,
                          BattleMode mode,
                          int hitsThisTurn);
};


#endif //A3_GIFTSYSTEM_H

#ifndef GAME_H
#define GAME_H

#include "Player.h"

enum BattleMode
{
    SWIFTSTRIKE = 1,
    STARLIGHT_CLASH,
    WRATH_OF_TITANS
};

class Game
{
private:
    Player*     players[2];
    BattleMode  mode;
    int         currentPlayer;   // 0 or 1
    int         rows;
    int         cols;

    void setupMode();
    void setupPlayers();
    void placementPhase();
    void battlePhase();
    void applyDiceEffect(Player& player);   // TODO: implement later
    bool checkVictory() const;
    void switchTurn();

public:
    Game();
    ~Game();

    void start();
};

#endif // GAME_H

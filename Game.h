#ifndef GAME_H
#define GAME_H

#include "Player.h"

// Battle modes
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

    void placementPhase();
    void battlePhase();
    bool checkVictory() const;
    void switchTurn();

public:
    Game(BattleMode mode,
         const char* name1,
         const char* name2,
         int rows,
         int cols);
    ~Game();

    void start();
};

#endif // GAME_H

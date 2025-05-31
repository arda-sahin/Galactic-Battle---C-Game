#include "Player.h"
#include <iostream>
#include <cstring>

static bool parseCoordinate(const char* str, Coordinate& out)
{
    if (str == 0 || str[0] == '\0' || str[1] == '\0')
        return false;

    char rowChar = str[0];
    if (rowChar < 'a' || rowChar > 'z')
        return false;

    int col = 0;
    for (int i = 1; str[i] != '\0'; ++i)
    {
        if (str[i] < '0' || str[i] > '9')
            return false;
        col = col * 10 + (str[i] - '0');
    }

    out.row = rowChar - 'a';
    out.col = col;
    return true;
}

// Constructor / Destructor
Player::Player(const char* playerName, int rows, int cols)
        : ownBoard(0),
          targetBoard(0),
          fleetSize(0),
          totalShots(0),
          hits(0),
          misses(0)
{
    std::memset(name, 0, 50);
    if (playerName != 0)
        std::strncpy(name, playerName, 50 - 1);

    ownBoard    = new Board(rows, cols);
    targetBoard = new Board(rows, cols);
}

Player::~Player()
{
    delete ownBoard;
    delete targetBoard;
    for (int i = 0; i < fleetSize; ++i)
        delete fleet[i];
}

// Fleet management
void Player::addShip(BattleShip* ship)
{
    if (fleetSize < 20 && ship != 0)
        fleet[fleetSize++] = ship;
}

int Player::remainingShips() const
{
    int cnt = 0;
    for (int i = 0; i < fleetSize; ++i)
        if (!fleet[i]->isSunk()) ++cnt;
    return cnt;
}

void Player::countRemainingTypes(int& sd,int& mc,int& xw,int& tie) const
{
    sd = mc = xw = tie = 0;
    for (int i = 0; i < fleetSize; ++i)
    {
        if (fleet[i]->isSunk()) continue;

        char sym = fleet[i]->getSymbol();
        if      (sym == '5') ++sd;
        else if (sym == '4') ++mc;
        else if (sym == '3') ++xw;
        else if (sym == '1') ++tie;
    }
}

int Player::maxLaserBursts() const
{
    int maxB = 0;
    for (int i = 0; i < fleetSize; ++i)
        if (!fleet[i]->isSunk() &&
            fleet[i]->getLaserBursts() > maxB)
            maxB = fleet[i]->getLaserBursts();
    return maxB;
}

// Deployment phase
void Player::deployFleet()
{
    std::cout << "\nCommander " << name << ", deploy your fleet.\n";

    for (int i = 0; i < fleetSize; ++i)
    {
        BattleShip* ship = fleet[i];
        bool placed = false;

        while (!placed)
        {
            std::cout << "Place ship (size " << ship->getSize()
                      << ", symbol '" << ship->getSymbol()
                      << "')\nEnter start and end coordinates (e.g., a1 a5): ";

            char sStr[10], eStr[10];
            std::cin >> sStr >> eStr;

            Coordinate start, end;
            if (!parseCoordinate(sStr, start) ||
                !parseCoordinate(eStr, end))
            {
                std::cout << "Invalid input. Try again.\n";
                continue;
            }

            if (ownBoard->placeShip(ship, start, end))
            {
                ownBoard->display(true);
                placed = true;
            }
            else
            {
                std::cout << "Cannot place there. Try again.\n";
            }
        }
    }
}

// Shooting phase – returns hits in this turn
int Player::takeTurn(Player& enemy)
{
    int shotsAllowed = maxLaserBursts();
    std::cout << "\n" << name << " shoots (" << shotsAllowed << " shots):\n";

    int hitsThisTurn = 0;

    for (int s = 0; s < shotsAllowed; ++s)
    {
        char coordStr[10];
        Coordinate target;
        bool valid = false;

        while (!valid)
        {
            std::cout << "  Shot #" << (s + 1) << ": ";
            std::cin >> coordStr;

            if (!parseCoordinate(coordStr, target) ||
                targetBoard->isOccupied(target))         // already shot here
            {
                std::cout << "  Invalid or repeated. Try again.\n";
            }
            else
            {
                valid = true;
            }
        }

        bool hit = enemy.ownBoard->markHit(target);
        char markChar = '0';                              // default = miss

        if (hit)
        {
            ++hits;
            ++hitsThisTurn;

            //locate the hit ship to update HP & get its symbol
            BattleShip* hitShip = 0;
            for (int i = 0; i < enemy.fleetSize && !hitShip; ++i)
            {
                BattleShip* ship = enemy.fleet[i];
                for (int c = 0; c < ship->getSize(); ++c)
                {
                    Coordinate cell = ship->cells[c];
                    if (cell.row == target.row && cell.col == target.col)
                    {
                        hitShip = ship;
                        break;
                    }
                }
            }

            if (hitShip)
            {
                hitShip->registerHit();
                markChar = hitShip->getSymbol();
                if (hitShip->isSunk())
                {
                    std::cout << "    >> " << enemy.getName()
                              << "'s ship (size " << hitShip->getSize()
                              << ") sunk!\n";
                }
            }
            else
            {
                markChar = '1';
            }
        }
        else
        {
            ++misses;
        }

        targetBoard->setCell(target, markChar);
        ++totalShots;
    }
    return hitsThisTurn;
}


// Reporting
const char* Player::getName() const { return name; }

void Player::printStats() const
{
    int sd, mc, xw, tie;
    countRemainingTypes(sd, mc, xw, tie);

    std::cout << name
              << "  |  Shots: "  << totalShots << "  Hits: " << hits << "  Misses: "  << misses
              << "  Remaining Ships: " << remainingShips()
              << " (" << "5:" << sd << ' ' << "4:" << mc << ' ' << "3:" << xw << ' ' << "1:" << tie << ")\n";
}

void Player::printBoards(bool /*revealShips*/) const
{
    std::cout << "\n=== " << name << " OWN BOARD ===\n";
    ownBoard->display(true);          // always reveal own ships

    std::cout << "\n=== " << name << " TARGET BOARD ===\n";
    targetBoard->display(true);       // show all info we discovered
}


Board* Player::getOwnBoard() const {
    return ownBoard;
}
Board* Player::getTargetBoard() const {
    return targetBoard;
}

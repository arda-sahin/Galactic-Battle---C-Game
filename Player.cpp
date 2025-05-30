#include "Player.h"
#include <iostream>
#include <cstring>    // For strncpy

// ------------------ Helper (local) ------------------
// Converts a coordinate string like "a4" to Coordinate.
// Returns true on success, false on failure.
static bool parseCoordinate(const char* str, Coordinate& out)
{
    if (str == nullptr || str[0] == '\0' || str[1] == '\0')
        return false;

    char rowChar = str[0];
    if (rowChar < 'a' || rowChar > 'z')
        return false;

    int col = 0;
    for (int i = 1; str[i] != '\0'; ++i)
    {
        if (str[i] < '0' || str[i] > '9') return false;
        col = col * 10 + (str[i] - '0');
    }
    out.row = rowChar - 'a';
    out.col = col;
    return true;
}

// ------------------ Constructor / Destructor ------------------
Player::Player(const char* playerName, int rows, int cols)
        : ownBoard(nullptr),
          targetBoard(nullptr),
          fleetSize(0),
          totalShots(0),
          hits(0),
          misses(0)
{
    // Copy name safely
    std::memset(name, 0, 50);
    if (playerName != nullptr)
    {
        std::strncpy(name, playerName, 50 - 1);
    }

    ownBoard    = new Board(rows, cols);
    targetBoard = new Board(rows, cols);
}

Player::~Player()
{
    delete ownBoard;
    delete targetBoard;

    for (int i = 0; i < fleetSize; ++i)
    {
        delete fleet[i];
    }
}

// ------------------ Fleet Management ------------------
void Player::addShip(BattleShip* ship)
{
    if (fleetSize < 20 && ship != nullptr)
    {
        fleet[fleetSize++] = ship;
    }
}

int Player::remainingShips() const
{
    int count = 0;
    for (int i = 0; i < fleetSize; ++i)
    {
        if (!fleet[i]->isSunk()) ++count;
    }
    return count;
}

int Player::getMaxOperativeBursts() const
{
    int maxBursts = 0;
    for (int i = 0; i < fleetSize; ++i)
    {
        if (!fleet[i]->isSunk())
        {
            int bursts = fleet[i]->getLaserBursts();
            if (bursts > maxBursts) maxBursts = bursts;
        }
    }
    return maxBursts;
}

// ------------------ Deployment Phase ------------------
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

            char startStr[10];
            char endStr[10];
            std::cin >> startStr >> endStr;

            Coordinate start, end;
            if (!parseCoordinate(startStr, start) ||
                !parseCoordinate(endStr, end))
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

// ------------------ Shooting Phase ------------------
void Player::takeTurn(Player& enemy)
{
    int shotsAllowed = getMaxOperativeBursts();
    std::cout << "\n" << name << " shoots now (can shoot "
              << shotsAllowed << "):\n";

    for (int s = 0; s < shotsAllowed; ++s)
    {
        char coordStr[10];
        Coordinate target;
        bool valid = false;

        while (!valid)
        {
            std::cout << "Enter coordinate #" << (s + 1) << ": ";
            std::cin >> coordStr;

            if (!parseCoordinate(coordStr, target) ||
                targetBoard->isOccupied(target))   // already shot here
            {
                std::cout << "Invalid or repeated coordinate. Try again.\n";
            }
            else
            {
                valid = true;
            }
        }

        bool hit = enemy.ownBoard->markHit(target);
        targetBoard->setCell(target, hit ? '*' : '0'); // '*' placeholder for hit

        ++totalShots;
        if (hit) ++hits;
        else     ++misses;
    }
}

// ------------------ Reporting ------------------
const char* Player::getName() const
{
    return name;
}

void Player::printStats() const
{
    std::cout << name << "  |  Shots: " << totalShots
              << "  Hits: " << hits
              << "  Misses: " << misses
              << "  Remaining Ships: " << remainingShips() << "\n";
}

void Player::printBoards(bool revealShips) const
{
    std::cout << "\n=== " << name << " OWN BOARD ===\n";
    ownBoard->display(revealShips);

    std::cout << "\n=== " << name << " TARGET BOARD ===\n";
    targetBoard->display(false);
}

// ------------------ Accessors ------------------
Board* Player::getOwnBoard() const
{
    return ownBoard;
}

Board* Player::getTargetBoard() const
{
    return targetBoard;
}

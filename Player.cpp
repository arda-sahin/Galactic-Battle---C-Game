#include "Player.h"
#include <iostream>
#include <cstring>

using namespace std;

// Parses a coordinate string like "a0", "b12", etc. Returns true on success.
static bool parseCoordinate(const char* str, Coordinate& out)
{
    // Check for null pointer
    if (str == nullptr){
        return false;}
    // Check that there is at least one character
    if (str[0] == '\0') {
        return false;}
    // Check that there is at least a second character
    if (str[1] == '\0') {
        return false;}
    // First character should be a lowercase letter for the row
    char rowChar = str[0];
    if (rowChar < 'a') {
        return false;}
    if (rowChar > 'z') {
        return false;}

    // column part
    int col = 0;
    int i = 1;

    while (str[i] != '\0') {
        char digitChar = str[i];
        if (digitChar < '0') {
            return false;}
        if (digitChar > '9') {
            return false;}

        int digit = digitChar - '0';
        col = col * 10 + digit;
        i = i + 1;
    }

    int row = rowChar - 'a';
    out.row = row;
    out.col = col;
    return true;
}

// constructor
Player::Player(const char* playerName, int rows, int cols)
        : ownBoard(nullptr),
          targetBoard(nullptr),
          fleetSize(0),
          totalShots(0),
          hits(0),
          misses(0),
          limitOneNextTurn(false),
          reduceOneNextTurn(false)
{
    if (playerName != nullptr) {
        strcpy(name, playerName);
    } else {
        name[0] = '\0';
    }

    ownBoard    = new Board(rows, cols);
    targetBoard = new Board(rows, cols);
}


Player::~Player()
{
    delete ownBoard;
    delete targetBoard;
    for (int i = 0; i < fleetSize; i++)
        delete fleet[i];
}

// Adds a ship
void Player::addShip(BattleShip* ship)
{
    // Check that fleetSize is less than maximum (20) and ship is not null
    if (fleetSize < 20 && ship != nullptr)
    {
        fleet[fleetSize] = ship;
        fleetSize = fleetSize + 1;
    }
}

// Returns the number of ships that have not been sunk
int Player::remainingShips() const{
    int cnt = 0;
    for (int i = 0; i < fleetSize; i = i + 1) {
        if (fleet[i]->isSunk() == false) {
            cnt = cnt + 1;
        }
    }
    return cnt;
}

void Player::countRemainingTypes(int& sd, int& mc, int& xw, int& tie) const
{
    //counters to zero
    sd = 0;
    mc = 0;
    xw = 0;
    tie = 0;

    // Loop over all ships in the fleet
    for (int i = 0; i < fleetSize; i = i + 1) {
        // Check if this ship is sunk
        bool sunk = fleet[i]->isSunk();
        if (sunk)
        {
            // Skip sunk ships
        }
        else {
            // Get the symbol for the ship type
            char sym = fleet[i]->getSymbol();

            if (sym == '5')
                sd = sd + 1;
            else if (sym == '4')
                mc = mc + 1;
            else if (sym == '3')
                xw = xw + 1;
            else if (sym == '1')
                tie = tie + 1;
        }
    }
}


int Player::maxLaserBursts() const {

    int maxBurst = 0;
    for (int i = 0; i < fleetSize; ++i)
        if (!fleet[i]->isSunk() && fleet[i]->getLaserBursts() > maxBurst)
            maxBurst = fleet[i]->getLaserBursts();
    return maxBurst;
}

// Deployment
void Player::deployFleet() {

    cout << "\n" << name << ", deploy your ships.\n";

    for (int i = 0; i < fleetSize; ++i) {

        BattleShip* ship = fleet[i];
        bool placed = false;

        while (!placed) {
            cout << "Place ship (size " << ship->getSize() << ", symbol '" << ship->getSymbol() << "')\nEnter start and end coordinates (Example: a0 a4): ";

            char sStr[10], eStr[10];
            cin >> sStr >> eStr;

            Coordinate start, end;
            if (!parseCoordinate(sStr, start) || !parseCoordinate(eStr, end)) {
                cout << "Invalid input. Try again.\n";
                continue;
            }
            if (ownBoard->placeShip(ship, start, end)) {
                ownBoard->display(true);
                placed = true;
            }
            else {
                cout << "Cannot place there. Try again.\n";}
        }
    }
}

// Shooting phase
int Player::takeTurn(Player& enemy){

    int shotsAllowed = maxLaserBursts();

    if (limitOneNextTurn) // force single shot
    {
        shotsAllowed = 1;
        limitOneNextTurn = false;
    }
    else if (reduceOneNextTurn)  // minus one shot
    {
        if (shotsAllowed > 1) shotsAllowed -= 1;
        reduceOneNextTurn = false;
    }

    cout << "\n" << name << " shoots (" << shotsAllowed << " shots):\n";

    int hitsThisTurn = 0;
    for (int s = 0; s < shotsAllowed; s++)
    {
        char crd[10];
        Coordinate target;
        bool valid = false;

        while (!valid) {
            cout << "  Shot: " << (s + 1) << ": ";
            cin >> crd;

            if (!parseCoordinate(crd, target) || targetBoard->isOccupied(target)) // already shot here
            {
                cout << "  Invalid or repeated. Try again.\n";}
            else{
                valid = true;}
        }

        bool hit = enemy.ownBoard->markHit(target);

        if (hit) {
            char rowLabel = (char)('a' + target.row);
            int  colLabel = target.col;
            cout <<"Hit at --> " << rowLabel << colLabel << "!\n";
        }

        char markChar = '0';

// If a hit on the target cell
        if (hit == true) {
            hits = hits + 1; // Increment total hits
            hitsThisTurn = hitsThisTurn + 1; // Increment hits

            BattleShip* hitShip;
            hitShip = nullptr;

            // Search enemy ship
            int i = 0;
            while (i < enemy.fleetSize){
                if (hitShip == nullptr){
                    BattleShip* ship;
                    ship = enemy.fleet[i];

                    int c = 0;
                    // Check each cell of this ship
                    while (c < ship->getSize()){
                        Coordinate cell;
                        cell = ship->cells[c];

                        // Compare the row and column with target coordinate
                        if (cell.row == target.row) {
                            if (cell.col == target.col) {
                                // Found the ship that was hit
                                hitShip = ship;
                                break;
                            }
                        }
                        c++;
                    }
                }
                i++;
            }

            // If a ship was found at the target cell
            if (hitShip != nullptr) {
                hitShip->registerHit(); // Register the hit on that ship
                markChar = hitShip->getSymbol(); // Use ship's symbol for marking

                // If the ship is now sunk
                if (hitShip->isSunk() == true)
                {
                    // Print a message
                    cout << "    >> "; cout << enemy.getName(); cout << "'s ship (size ";
                    cout << hitShip->getSize(); cout << ") sunk!\n";

                    // Mark all cells of the sunk ship on the target board
                    int k = 0;
                    while (k < hitShip->getSize()) {
                        Coordinate sc;
                        sc = hitShip->cells[k];
                        targetBoard->setCell(sc, hitShip->getSymbol());
                        k++;
                    }
                }
            }
            else{
                // No ship found at that cell, mark as a miss symbol '1'
                markChar = '1';}
        }
        else {
            misses++; }
        targetBoard->setCell(target, markChar);
        totalShots++;

        //  If enemy has no ships left, stop the loop
        if (enemy.remainingShips() == 0){
            break;
        }
    }

    return hitsThisTurn;
}

// Statistics
const char* Player::getName() const {
    return name;
}

void Player::printStats() const {
    int sd, mc, xw, tie;
    countRemainingTypes(sd, mc, xw, tie);

    cout << name
              << "  |  Shots: "  << totalShots << "  Hits: " << hits << "  Misses: "  << misses
              << "  Remaining Ships: " << remainingShips()
              << " (" << "StarDestroyer:" << sd << ' ' << "MonCalamariCruiser:" << mc << ' ' << "XWingSquadron:" << xw << ' ' << "TIEFighter:" << tie << ")\n";
}

void Player::printBoards(bool) const {
    cout << "\n" << name << "    OWN BOARD\n";
    ownBoard->display(true);

    cout << "\n" << name << "    TARGET BOARD\n";
    targetBoard->display(true);
}


Board* Player::getOwnBoard() const {
    return ownBoard;
}
Board* Player::getTargetBoard() const {
    return targetBoard;
}
void Player::setLimitOneNextTurn(){
    limitOneNextTurn  = true;
}
void Player::setReduceOneNextTurn() {
    reduceOneNextTurn = true; }
int  Player::getFleetSize() const  {
    return fleetSize; }


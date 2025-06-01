#include "Board.h"
#include "BattleShip.h"
#include <iostream>
using namespace std;

// Constructor
Board::Board(int r, int c) : rows(r), cols(c)
{
    // Initialize grid
    grid = new char*[rows];
    for (int i = 0; i < rows; ++i)
    {
        grid[i] = new char[cols];
        for (int j = 0; j < cols; ++j)
        {
            grid[i][j] = '*';  // Empty cell
        }
    }
}

// Destructor
Board::~Board()
{
    for (int i = 0; i < rows; ++i)
    {
        delete[] grid[i];
    }
    delete[] grid;
}

// Returns true if cordinate is within the board boundaries
bool Board::isInside(const Coordinate& cordinate) const {
    // Check row bounds
    if (cordinate.row < 0 || cordinate.row >= rows) {
        return false;
    }
    // Check column bounds
    if (cordinate.col < 0 || cordinate.col >= cols) {
        return false;
    }
    return true;
}


bool Board::isOccupied(const Coordinate& coord) const {
    return grid[coord.row][coord.col] != '*';
}


bool Board::placeShip(BattleShip* ship, const Coordinate& start, const Coordinate& end) {
    // one cell ship
    if (ship->getSize() == 1) {
        if (!isInside(start) || isOccupied(start) || start.row != end.row || start.col != end.col)
            return false;

        grid[start.row][start.col] = ship->getSymbol();
        ship->cells[0] = start;
        return true;
    }

// directions
// Determine row step direction: +1 if end is below start, -1 if above, 0 if same row
    int dRow;
    if (end.row > start.row) {
        dRow = 1;
    } else if (end.row < start.row) {
        dRow = -1;
    } else {
        dRow = 0;
    }

// Determine column step direction: +1 if end is to the right, -1 if to the left, 0 if same column
    int dCol;
    if (end.col > start.col) {
        dCol = 1;}
    else if (end.col < start.col) {
        dCol = -1;}
    else {
        dCol = 0; }


    if (dRow == 0 && dCol == 0)
        return false;

    if (dRow != 0 && dCol != 0 && (dRow != dCol && dRow != -dCol))
        return false;

// Initialize length and set current position to start
    int length = 0;
    Coordinate cur = start;

// Loop until we reach the end cell
    while (true) {
        // If current cell is outside the board or occupied, return false
        if (!isInside(cur) || isOccupied(cur)) {
            return false;
        }

        length = length + 1;

        // If we've reached the end, exit the loop
        if (cur.row == end.row && cur.col == end.col) {
            break;
        }

        cur.row = cur.row + dRow;
        cur.col = cur.col + dCol;
    }


    if (length != ship->getSize())
        return false;

    cur = start;
    int idx = 0;

// Continue until the end coordinate is reached
    while (true) {
        // Place ship symbol
        grid[cur.row][cur.col] = ship->getSymbol();
        ship->cells[idx] = cur;
        idx = idx + 1;

        // Check if current coordinate is the end coordinate
        if (cur.row == end.row && cur.col == end.col) {
            break;
        }

        cur.row = cur.row + dRow;
        cur.col = cur.col + dCol;
    }

    return true;
}

bool Board::markHit(const Coordinate& coord) {
    if (!isInside(coord)) return false;

    char &cell = grid[coord.row][coord.col];

    if (cell == '*') {
        cell = '0';
        return false;
    }
    if (cell == '0')
        return false;

    return true;
}

char Board::getCell(const Coordinate& coord) const
{
    return grid[coord.row][coord.col];
}

void Board::setCell(const Coordinate& coord, char value)
{
    grid[coord.row][coord.col] = value;
}

void Board::display(bool revealShips) const
{
    cout << "   ";
    for (int c = 0; c < cols; ++c) {
        cout << c << ' '; }
    cout << endl;

    for (int r = 0; r < rows; ++r) {
        cout << (char)('a' + r) << "  ";
        for (int c = 0; c < cols; ++c) {
            char ch = grid[r][c];
            if (!revealShips && ch >= '1' && ch <= '9')
                ch = '*';

            cout << ch << ' ';
        }
        cout << endl;
    }
}

int Board::getRows() const {
    return rows;
}

int Board::getCols() const {
    return cols;
}
#include "Board.h"
#include "BattleShip.h"
#include <iostream>

// Constructor
Board::Board(int r, int c) : rows(r), cols(c)
{
    // Allocate 2-D grid
    grid = new char*[rows];
    for (int i = 0; i < rows; ++i)
    {
        grid[i] = new char[cols];
        for (int j = 0; j < cols; ++j)
        {
            grid[i][j] = '*';    // Empty cell indicator
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

bool Board::isInside(const Coordinate& coord) const
{
    return coord.row >= 0 && coord.row < rows &&
           coord.col >= 0 && coord.col < cols;
}

bool Board::isOccupied(const Coordinate& coord) const
{
    return grid[coord.row][coord.col] != '*';
}

// Place ship between start and end (inclusive)
// Works for horizontal, vertical and diagonal (45°) placements
bool Board::placeShip(BattleShip* ship,
                      const Coordinate& start,
                      const Coordinate& end)
{
    // Direction deltas
    int dRow = (end.row > start.row) ? 1 : (end.row < start.row ? -1 : 0);
    int dCol = (end.col > start.col) ? 1 : (end.col < start.col ? -1 : 0);

    // Validate direction
    if (dRow == 0 && dCol == 0) return false;            // Same cell
    if (dRow != 0 && dCol != 0 && (dRow != dCol)) return false; // Not 45°

    // Collect cells along the path
    int length = 0;
    Coordinate cur = start;
    while (true)
    {
        if (!isInside(cur) || isOccupied(cur)) return false;

        ++length;
        if (cur.row == end.row && cur.col == end.col) break;

        cur.row += dRow;
        cur.col += dCol;
    }

    // Length must match ship size
    if (length != ship->getSize()) return false;

    // Second pass: actually place the ship
    cur = start;
    int index = 0;
    while (true)
    {
        grid[cur.row][cur.col] = ship->getSymbol();
        ship->cells[index++]   = cur;

        if (cur.row == end.row && cur.col == end.col) break;
        cur.row += dRow;
        cur.col += dCol;
    }

    return true;
}

// Mark a coordinate as shot; returns true if it was a hit
bool Board::markHit(const Coordinate& coord)
{
    if (!isInside(coord)) return false;

    char& cell = grid[coord.row][coord.col];
    if (cell == '*')      // Miss
    {
        cell = '0';
        return false;
    }
    if (cell == '0')      // Already shot here
    {
        return false;
    }

    // Hit on a ship cell; convert to '0' for future reference
    cell = '0';
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
    std::cout << "   ";
    for (int c = 0; c < cols; ++c)
    {
        std::cout << c << ' ';
    }
    std::cout << std::endl;

    for (int r = 0; r < rows; ++r)
    {
        std::cout << (char)('a' + r) << "  ";
        for (int c = 0; c < cols; ++c)
        {
            char ch = grid[r][c];
            if (!revealShips && ch != '*' && ch != '0')
            {
                ch = '*';   // Hide ships when not revealing
            }
            std::cout << ch << ' ';
        }
        std::cout << std::endl;
    }
}

int Board::getRows() const
{
    return rows;
}

int Board::getCols() const
{
    return cols;
}

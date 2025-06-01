#include "Coordinate.h"

// Default constructor: set row and col to 0
Coordinate::Coordinate()
{
    row = 0;
    col = 0;
}

// Constructor with parameters: set row and col to given values
Coordinate::Coordinate(int r, int c)
{
    row = r;
    col = c;
}

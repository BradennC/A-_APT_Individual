//
// Created by Quinn Goh on 22/1/23.
//

#include "Tile.h"
#include <ostream>

#ifndef A2_APT_BOARDLOCATION_H
#define A2_APT_BOARDLOCATION_H


// Class representing a location on the game board
class BoardLocation {
public:
    // Constructor with just the column and row position
    BoardLocation(int column, int row);

    // Constructor with column, row and a tile at that position
    BoardLocation(int column, int row, Tile tile);

    // Copy constructor
    BoardLocation(const BoardLocation &other);

    // Get the row of the location
    int row() const;

    // Get the column of the location
    char column() const;

    // Get the tile at this location
    const Tile tile() const;

    // Alias for `tile`
    const Tile getTile() const;

    // Get the column position
    int getCol() const;

    // Get the row position
    int getRow() const;

private:
    int x;
    int y;
    Tile boardTile;
};

#endif //A2_APT_BOARDLOCATION_H

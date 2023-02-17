#include <iostream>
#include "Tile.h"
#include "BoardLocation.h"


BoardLocation::BoardLocation(int column, int row) {
    x = row;
    y = column;
}

BoardLocation::BoardLocation(int column, int row, Tile tile) {
    x = row;
    y = column;
    boardTile = tile;
}

BoardLocation::BoardLocation(const BoardLocation &other) {
    y = other.y;
    x = other.x;
    boardTile = other.boardTile;
}

int BoardLocation::row() const {
    return x;
}

char BoardLocation::column() const {
    return (char) (y);
}

const Tile BoardLocation::tile() const {
    return boardTile;
}

const Tile BoardLocation::getTile() const {
    return this->boardTile;
}

int BoardLocation::getCol() const {

    return this->x;
}

int BoardLocation::getRow() const {

    return this->y;
}
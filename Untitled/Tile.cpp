#include "Tile.h"

Tile::Tile() {
    this->colour = ' ';
    this->shape = 0;
};

Tile::Tile(char colour, int shape) {
    this->colour = colour;
    this->shape = shape;
}

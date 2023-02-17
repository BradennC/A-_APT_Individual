#include "TileBag.h"
#include <iostream>

TileBag::TileBag() {
    this->tiles = nullptr;
};

TileBag::TileBag(LinkedList* tiles) {
    this->tiles = tiles;
};

TileBag::~TileBag() {
    delete this->tiles;
};

Tile* TileBag::drawTile() {
    if (tiles->isEmpty()) {
        throw std::out_of_range("Tile bag is empty, cannot draw tile.");
    }
    Tile* drawnTile = tiles->getHead()->tile;
    tiles->deleteFront();
    return drawnTile;
}

void TileBag::addTile(Tile* tile)
{
    this->tiles->addBack(tile);
}


bool TileBag::isEmpty() {
    if(this->tiles->isEmpty()){
        return true;
    } else {
        return false;
    }
}

void TileBag::clearTiles() {
    this->tiles->clear();
}

void TileBag::addTileList(LinkedList* list) {
    if(!this->tiles->isEmpty()){
        throw std::logic_error("List Must be empty for this!");
    } else {
        this->tiles = list;
    }
};

LinkedList* TileBag::getTileList() {
    return this->tiles;
};



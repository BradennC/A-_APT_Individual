#ifndef ASSIGN2_TILEBAG
#define ASSIGN2_TILEBAG

#include "LinkedList.h"
#include "Tile.h"

class TileBag {
public:
    /**
     * @brief Constructor
     *
     * Initializes the the tileBag;
     */
    TileBag();

    /**
     * @brief Constructor
     *
     * Initializes the the tileBag with a pre made list of tiles;
     */
    TileBag(LinkedList* tiles);

    /**
     * @brief deconstructor
     *
     * Deletes list of tiles, tiles are the only memory on the heap.
     */
    ~TileBag();

    /**
     * @brief draws tile from tile list
     *
     * Throws out of range error if tile bag is empty
     * 
     * @return the tile drawn is returned to its caller
     */
    Tile* drawTile();

    /**
     * @brief check if tile list is empty
     *
     * @return returns bool value depending on state of tile list
     */
    bool isEmpty();

    /**
     * @brief tile list deleter
     *
     * Will clear it's tile list by calling linkedlist function.
     */
    void clearTiles();

    /**
     * @brief can add tile list to object
     *
     * @param list accepts a premade linked list and redefines object member value
     */
    void addTileList(LinkedList* list);

    /**
     * @brief adds an argument to it's list var
     *
     * @param tile tile to be added
     */
    void addTile(Tile* tile);

    /**
     * @brief adds an argument to it's list var
     *
     * @param tile tile to be added
     */
    LinkedList* getTileList();

    // Pointer to list variable stored on the heap
    // list pointer is a public variable for visibilty across calling classes
    LinkedList* tiles;
};

#endif // ASSIGN2_TILEBAG